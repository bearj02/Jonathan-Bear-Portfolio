from pathlib import Path
from rosbags.highlevel import AnyReader
from rosbags.typesys import Stores, get_typestore, get_types_from_idl, get_types_from_msg
from tf_transformations import euler_from_quaternion
import matplotlib.pyplot as plt
import numpy as np
import allan_variance
from scipy import integrate, signal, interpolate
import math
         
def load_ros2_bag_data(bagfile):
    imu_data = {'time': [], 'accel': [], 'gyro': [], 'orientation': [], 'mag': []}
    gps_data = {'time': [], 'easting':[],'northing':[],'zone':[],'letter':[]}
    
    bagpath = Path(bagfile)

    imu_text = Path('imu_interfaces/msg/IMUmsg.msg').read_text()
    gps_text = Path('gps_interfaces/msg/GPSmsg.msg').read_text()

    typestore = get_typestore(Stores.ROS2_HUMBLE)

    add_types = {}
    add_types.update(get_types_from_msg(imu_text, 'imu_interfaces/msg/IMUmsg'))
    add_types.update(get_types_from_msg(gps_text, 'gps_interfaces/msg/GPSmsg'))

    typestore.register(add_types)
    with AnyReader([bagpath], default_typestore=typestore) as reader:
        imu_connections = [x for x in reader.connections if x.topic == '/imu']
        gps_connections = [y for y in reader.connections if y.topic == '/gps']

        for connection, timestamp, rawdata in reader.messages(connections=imu_connections):
            msg = reader.deserialize(rawdata, connection.msgtype)

            accel_x = msg.imu.linear_acceleration.x
            accel_y = msg.imu.linear_acceleration.y
            accel_z = msg.imu.linear_acceleration.z

            gyro_x = msg.imu.angular_velocity.x
            gyro_y = msg.imu.angular_velocity.y
            gyro_z = msg.imu.angular_velocity.z

            mag_x = msg.mag_field.magnetic_field.x
            mag_y = msg.mag_field.magnetic_field.y
            mag_z = msg.mag_field.magnetic_field.z

            time_s = msg.header.stamp.sec
            time_ns = msg.header.stamp.nanosec
            time = time_s + time_ns/1e9

            imu_data['time'].append(time)
            imu_data['accel'].append([accel_x, accel_y, accel_z])
            imu_data['gyro'].append([gyro_x, gyro_y, gyro_z])
            imu_data['orientation'].append([msg.imu.orientation.x, msg.imu.orientation.y, msg.imu.orientation.z, msg.imu.orientation.w])
            imu_data['mag'].append([mag_x, mag_y, mag_z])
        
        for connection, timestamp, rawdata in reader.messages(connections=gps_connections):
            msg = reader.deserialize(rawdata, connection.msgtype)

            utm_easting = msg.utm_easting
            utm_northing = msg.utm_northing
            utm_zone = msg.zone
            utm_letter = msg.letter

            time_s = msg.header.stamp.sec
            time_ns = msg.header.stamp.nanosec
            time = time_s + time_ns/1e9

            gps_data['time'].append(time)
            gps_data['easting'].append(utm_easting)
            gps_data['northing'].append(utm_northing)
            gps_data['zone'].append(utm_zone)
            gps_data['letter'].append(utm_letter)

    return imu_data, gps_data

def convert_to_euler(orientations):
    euler_angles = []
    for quat in orientations:
        roll, pitch, yaw = euler_from_quaternion(quat)
        euler_angles.append([roll, pitch, yaw])
    return np.array(euler_angles)

def compute_statistics(data):
    data_np = np.array(data)
    mean = np.mean(data_np, axis=0)
    std_dev = np.std(data_np, axis=0)
    return mean, std_dev

def get_magcal_matrix(mag_data):
    mag_data_np = np.array(mag_data)
    meanx = np.mean(mag_data_np[:,0])
    meany = np.mean(mag_data_np[:,1])

    x = mag_data_np[:,0].T
    y = mag_data_np[:,1].T

    D = np.c_[x**2, x*y, y**2, x, y, np.ones_like(x)]
    S = np.dot(D.T, D)

    eigvals, eigvecs = np.linalg.eig(S)
    min_eigval_index = np.argmin(eigvals)
    ellipse_params = eigvecs[:, min_eigval_index]
    
    center_x = -ellipse_params[3] / (2 * ellipse_params[0])
    center_y = -ellipse_params[4] / (2 * ellipse_params[2])
    
    xh = x - center_x
    yh = y - center_y

    Dh = np.c_[xh**2, xh*yh, yh**2, xh, yh, np.ones_like(xh)]
    Sh = np.dot(Dh.T, Dh)
    evalsh, evecsh = np.linalg.eig(Sh)
    min_eigvalh_index = np.argmin(evalsh)
    ellipseh_params = evecsh[:, min_eigvalh_index]

    semi_major = np.sqrt(1 / ellipseh_params[0])
    semi_minor = np.sqrt(1 / ellipseh_params[2])

    rotation = 0.5 * np.arctan2(ellipseh_params[1], ellipseh_params[0] - ellipseh_params[2])

    scale_x = 1 / semi_major
    scale_y = 1 / semi_minor

    H = np.array([
        [scale_x * np.cos(rotation), -scale_y * np.sin(rotation), 0],
        [scale_x * np.sin(rotation), scale_y * np.cos(rotation), 0],
        [0, 0, 1]
    ])

    return H, center_x, center_y
    

def plot_time_series(time, data, title, ylabel):
    plt.figure(figsize=(10, 6))
    plt.plot(time, data)
    plt.title(title)
    plt.xlabel("Time [s]")
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.show()

def plot_magcal(x, y, xcenter, ycenter, xcal, ycal, title, xlabel, ylabel):
    plt.figure(figsize=(10, 6))
    plt.scatter(x, y, color='blue', label='Raw Mag Data')
    plt.scatter(xcenter,ycenter, color='red')
    plt.scatter(xcal,ycal, color='purple', label='Calibrated Mag Data')
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.legend()
    plt.show()

def plot_histogram(data, title, xlabel):
    plt.figure(figsize=(10, 6))
    plt.hist(data, bins=50, alpha=0.75)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel("Frequency")
    plt.grid(True)
    plt.show()

def plot_allan_deviation(data, title):
    plt.figure(figsize=(10,6))
    dt = 1 / 40
    tau, avar = allan_variance.compute_avar(data,dt)
    plt.loglog(tau, avar, '.')
    plt.xlabel("Averaging time, s")
    plt.ylabel("Allan Variance")
    plt.title(title)
    plt.grid(True)
    plt.show()

def plot_time_series_comparison(time, data1, label1, data2, label2, title, ylabel):
    plt.figure(figsize=(10, 6))
    plt.plot(time, data1, label=label1)
    plt.plot(time, data2, label=label2)
    plt.title(title)
    plt.xlabel("Time [s]")
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.legend()
    plt.show()

def plot_3_time_series(time, data1, label1, data2, label2, data3, label3, title, ylabel):
    plt.figure(figsize=(10, 6))
    plt.plot(time, data1, label=label1)
    plt.plot(time, data2, label=label2)
    plt.plot(time, data3, label=label3)
    plt.title(title)
    plt.xlabel("Time [s]")
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.legend()
    plt.show()

def plot_2time_comparison(imu_time, imu_vel, gps_time, gps_vel, label1, label2, title, ylabel):
    plt.figure(figsize=(10, 6))
    plt.plot(imu_time,imu_vel,label=label1)
    plt.plot(gps_time, gps_vel, label=label2)
    plt.title(title)
    plt.xlabel("Time [s]")
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.legend()
    plt.show()

def plot_path_comparison(imu_xe, imu_xn, gps_xe, gps_xn):
    plt.figure(figsize=(10, 6))
    plt.plot(imu_xe, imu_xn, label="IMU Path from Dead Reckoning")
    plt.plot(gps_xe, gps_xn, label="GPS Path")
    plt.title("Path from GPS vs. Dead Reckoning Estimated Path from IMU")
    plt.xlabel("Easting [m]")
    plt.ylabel("Northing [m]")
    plt.grid(True)
    plt.legend()
    plt.show()

def wrap_to_pi(data):
    data_wrapped_to_pi = np.remainder(data, 2*np.pi)
    mask = np.abs(data_wrapped_to_pi)>np.pi
    data_wrapped_to_pi[mask] -= 2*np.pi*np.sign(data_wrapped_to_pi[mask])
    return data_wrapped_to_pi


def butter_lowpass(cutoff, fs, order=5):
    sos = signal.butter(order, cutoff, 'lowpass', fs=fs, analog=False, output='sos')
    return sos

def butter_lowpass_filter(data, cutoff, fs, order=5):
    sos = butter_lowpass(cutoff, fs, order=order)
    y = signal.sosfilt(sos, data)
    return y

def butter_highpass(cutoff, fs, order=5):
    b,a = signal.butter(order, cutoff, 'highpass', fs=fs, analog=False, output='ba')
    return b,a

def butter_highpass_filter(data, cutoff, fs, order=5):
    b,a = butter_highpass(cutoff, fs, order=order)
    y = signal.filtfilt(b,a, data)
    return y

def butter_bandpass(lcutoff, hcutoff, fs, order=5):
    b,a = signal.butter(order, [lcutoff, hcutoff], btype='bandpass', fs=fs, analog=False)
    return b,a

def butter_bandpass_filter(data, lcutoff, hcutoff, fs, order=5):
    nyq = 0.5*fs
    low = lcutoff / nyq
    high = hcutoff / nyq
    b,a = butter_bandpass(low, high, fs, order=order)
    y = signal.filtfilt(b,a, data)
    return y

def complementary_filter(gyro_data, mag_data, alpha=0.98):
    filtered_angle = np.zeros_like(mag_data)
    for i in range(1, len(gyro_data)):
        filtered_angle[i] = (alpha * (gyro_data[i]) +
                             (1 - alpha) * mag_data[i])
    return filtered_angle

def gps_forward_velocity(time, easting, northing):
    velocities = [0]
    for i in range(len(easting)-1):
        dt = time[i+1]-time[i]
        distance = np.sqrt((easting[i+1]-easting[i])**2 + (northing[i+1]-northing[i])**2)
        if(dt > 0):
            velocity = distance / dt
            velocities.append(velocity)
        else:
            velocities.append(velocities[-1])
    return velocities

def imu_forward_velocity(time, for_acc):
    velocities = [0]
    for i in range(1, len(for_acc)):
        dt = time[i] - time[i-1]
        velocity = velocities[-1] + 0.5*dt*(for_acc[i]+for_acc[i-1])
        if velocity > 0:
            velocities.append(velocity)
        else:
            velocities.append(0)
    return velocities

def pos(list):
    return [max(x, 0) for x in list]

def dead_reckoning(for_vel, yaw):
    yaw += np.arctan2(40,10)-np.pi
    vn = []
    ve = []
    for i in range(0,len(for_vel)):
        vn.append(for_vel[i] * np.sin(yaw[i]))
        ve.append(for_vel[i] * -np.cos(yaw[i]))
    return vn, ve

def derivative(data, time):
    if len(data) == len(time):
        val = 0
        if time[1]-time[0] > 0:
            val = (data[1]-data[0])/(time[1]-time[0])
        deriv = [val]
        for i in range(1,len(data)-1):
            val = 0
            if time[i+1]-time[i-1] > 0:
                val = (data[i+1]-data[i-1])/(time[i+1]-time[i-1])
            deriv.append(val)
        val = 0
        if time[-1]-time[-2] > 0:
            val = (data[-1]-data[-2])/(time[-1]-time[-2])
        deriv.append(val)
        return deriv

def resample_data(time1, data1, time2, data2, new_time_interval):
    start_time = max(time1[0], time2[0])
    end_time = min(time1[-1], time2[-1])
    new_time = np.arange(start_time, end_time, new_time_interval)

    interp_func1 = interpolate.interp1d(time1, data1, bounds_error=False, fill_value='extrapolate')
    resampled_data1 = interp_func1(new_time)

    interp_func2 = interpolate.interp1d(time2, data2, bounds_error=False, fill_value='extrapolate')
    resampled_data2 = interp_func2(new_time)

    return new_time, resampled_data1, resampled_data2

def calibrate_accel_data(for_acc, imu_time, gps_vel, gps_time):
    for_acc = for_acc - np.mean(for_acc)
    zeros = np.nonzero(np.asarray(gps_vel) == 0)[0]
    consecutives = []
    if len(zeros) > 1:
        prev_end = 0
        for i in range(1, len(zeros)):
            if zeros[i] == zeros[i - 1] + 1:
                if i == 1 or zeros[i - 1] != zeros[i - 2] + 1:
                    start_index = zeros[i - 1]
                if i == len(zeros) - 1 or zeros[i + 1] != zeros[i] + 1:
                    end_index = zeros[i]
                    if prev_end > 0:
                        consecutives.append((prev_end+1, start_index))
                    prev_end = end_index
    prev_start = 0
    for end,start in consecutives:
        imu_start = np.abs(imu_time - gps_time[start]).argmin()
        imu_end = np.abs(imu_time - gps_time[end]).argmin()
        stop_mean = np.mean(np.array(for_acc)[prev_start:imu_end])
        for_acc[prev_start:-1] -= stop_mean
        mean = np.mean(np.array(for_acc)[imu_end:imu_start])
        for_acc[imu_end:-1] -= (mean)
        for_acc[prev_start:imu_end] = 0
        prev_start = imu_start

    return for_acc

# Main function to analyze ros2 bag data
def analyze_imu_data(circlebag, drivingbag):
    circle_imu_data, circle_gps_data = load_ros2_bag_data(circlebag)
    driving_imu_data, driving_gps_data = load_ros2_bag_data(drivingbag)
    
    plot_verbose = 0

    ### PART 1 ###

    # Find Magnetometer Distortions using get_magcal_matrix function
    calibration_matrix, center_x, center_y = get_magcal_matrix(circle_imu_data['mag'])
    xc = np.array(circle_imu_data['mag'])[:,0]
    yc = np.array(circle_imu_data['mag'])[:,1]
    circle_calibrated_coords = calibration_matrix@(np.vstack([xc-center_x,yc-center_y,np.ones_like(xc).T]))

    if plot_verbose:
        plot_magcal(xc, yc, center_x, center_y, circle_calibrated_coords[0], circle_calibrated_coords[1],"Circle Driving Magnetometer Data","Mag X [T]","Mag Y [T]")
    
    # Calibrate the magnetometer when driving using distortions found from circle data
    imu_time = np.array(driving_imu_data['time'])-driving_imu_data['time'][0]
    gps_time = np.array(driving_gps_data['time'])-driving_gps_data['time'][0]
    xd = np.array(driving_imu_data['mag'])[:,0]
    yd = np.array(driving_imu_data['mag'])[:,1]
    raw_yaw = np.arctan2(xd, yd)
    driving_calibrated_coords = calibration_matrix@(np.vstack([xd-center_x,yd-center_y,np.ones_like(xd).T]))
    calibrated_yaw = np.arctan2(driving_calibrated_coords[0], driving_calibrated_coords[1])

    if plot_verbose:
        plot_time_series_comparison(imu_time,raw_yaw, "Yaw Angle from Observed Magnetometer data", calibrated_yaw, "Yaw Angle from Calibrated Magnetometer Data", "Yaw Angle from Magnetometer", "Yaw [rad]")

    # Find yaw angle by integrating the observed angular velocity about the Z axis of the gyroscope
    gyroZ = np.array(driving_imu_data['gyro'])[:,2]
    yaw_from_gyro = integrate.cumulative_trapezoid(gyroZ,imu_time,initial=0)
    yaw_from_gyro = yaw_from_gyro-(yaw_from_gyro[0]-calibrated_yaw[0])
    yaw_from_gyro_final = wrap_to_pi(yaw_from_gyro)

    if plot_verbose:
        plot_time_series_comparison(imu_time,yaw_from_gyro_final, "Yaw Angle Integrated from Gyro", calibrated_yaw, "Yaw Angle from Calibrated Magnetometer Data", "Yaw Angle from Gyro vs. Magnetometer", "Yaw [rad]")

    # Apply a complementary filter to obtain an estimate of the actual yaw angle
    alpha = 0.9
    gyro_hpf = alpha * yaw_from_gyro_final
    mag_lpf = (1 - alpha) * calibrated_yaw
    filtered_yaw = wrap_to_pi(gyro_hpf + mag_lpf)

    if plot_verbose:
        plot_3_time_series(imu_time,mag_lpf, "Calibrated Magnetometer Yaw Through Low Pass Filter", gyro_hpf, "Integrated Gyroscope Yaw Through High Pass Filter", filtered_yaw, "Yaw from Complementary Filter", "Yaw Angle produced by LP, HP, and Complementary Filters", "Yaw [rad]")

    # Compare the Yaw from the complementary filter to the yaw observed by the IMU
    euler_angles = convert_to_euler(driving_imu_data['orientation'])
    imu_yaw = np.array(euler_angles)[:,2]
    imu_yaw = wrap_to_pi(imu_yaw-(imu_yaw[0]-filtered_yaw[0]))

    if plot_verbose:
        plot_time_series_comparison(imu_time, imu_yaw, "IMU Yaw Reading", filtered_yaw, "Complementary Filter Yaw Estimate", "Estimated Yaw vs. IMU Yaw", "Yaw[rad]")


    ### PART 2 ###

    # Determine the forward velocity of the vehicle from gps data
    for_vel_gps = gps_forward_velocity(gps_time,driving_gps_data['easting'],driving_gps_data['northing'])

    # Determine the forward velocity of the vehicle by integrating the accelerometer data
    for_acc = np.array(driving_imu_data['accel'])[:,0]
    for_vel_imu = np.array(integrate.cumulative_trapezoid(for_acc,imu_time,initial=0))
    if plot_verbose:
        plot_2time_comparison(imu_time, for_vel_imu, gps_time, for_vel_gps, "Velocity Estimate from IMU Before Calibration", "Velocity Estimate from GPS", "Velocity Estimate from IMU and GPS before calibration", "Velocity [m/s]")

    # Calibrate the accelerometer data
    for_acc = 1.96*calibrate_accel_data(for_acc, imu_time, for_vel_gps,gps_time)
    for_vel_imu_calibrated = np.array(pos(integrate.cumulative_trapezoid(for_acc,imu_time,initial=0)))
    if plot_verbose:
        plot_2time_comparison(imu_time, for_vel_imu_calibrated, gps_time, for_vel_gps, "Velocity Estimate from IMU After Calibration", "Velocity Estimate from GPS", "Velocity Estimate from IMU and GPS after calibration", "Velocity [m/s]")

    # Calculate displacement by integrating the forward velocity
    imu_displacement = integrate.cumulative_trapezoid(for_vel_imu_calibrated, imu_time, initial=0)
    gps_displacement = integrate.cumulative_trapezoid(for_vel_gps, gps_time, initial=0)
    if plot_verbose:
        plot_2time_comparison(imu_time, imu_displacement, gps_time, gps_displacement, "Displacement from IMU Forward Velocity", "Displacement from GPS Forward Velocity", "Displacement from Integrated Velocity", "Displacement [m]")

    # Compare y_accel_obs to omega * X_vel
    y_obs = np.array(driving_imu_data['accel'])[:,1]
    omega_xvel = for_vel_imu_calibrated * gyroZ
    if plot_verbose:
        plot_time_series_comparison(imu_time, y_obs, "Y_dot_dot observed", omega_xvel, "Omega * X_dot", "Y accel comparison", "Accel Y [m/s^2]")
    
    # Calculate the path of the car using dead reckoning for the imu
    imu_vn, imu_ve = dead_reckoning(for_vel_imu_calibrated, filtered_yaw)
    imu_xn = integrate.cumulative_trapezoid(imu_vn, imu_time, initial=0)
    imu_xe = integrate.cumulative_trapezoid(imu_ve, imu_time, initial=0)

    # Calculate the path of the car using gps data
    gps_xe = np.array(driving_gps_data['easting'])
    gps_xe = gps_xe - gps_xe[0]
    gps_xn = np.array(driving_gps_data['northing'])
    gps_xn = gps_xn - gps_xn[0]

    if plot_verbose:
        plot_path_comparison(imu_xe, imu_xn, gps_xe, gps_xn)

    ### ONLY UNCOMMENT THIS SECTION TO DETERMINE WHEN THE PATHS DIFFER SIGNIFICANTLY ###

    # std_time, imu_xe_adj, gps_xe_adj = resample_data(imu_time, imu_xe, gps_time, gps_xe, 0.1)
    # std_time, imu_xn_adj, gps_xn_adj = resample_data(imu_time, imu_xn, gps_time, gps_xn, 0.1)

    # for i in range(len(std_time)):
    #     diff = np.sqrt((imu_xe_adj[i] - gps_xe_adj[i])**2 + (imu_xn_adj[i] - gps_xn_adj[i])**2)
    #     if diff > 2:
    #         print(std_time[i])
    #         break


    ### Extra Credit ###

    # gps_heading = np.arctan2(-gps_xe, gps_xn)
    # gps_ang_vel = np.array(derivative(gps_heading,gps_time))
    # gps_ang_acc = np.array(derivative(gps_ang_vel, gps_time))

    # y_accel_v = np.array(derivative(derivative(gps_xe, gps_time),gps_time))
    # x_vel_v = np.array(derivative(gps_xn, gps_time))
    # y_accel_obs = np.array(resample_data(y_obs, imu_time, gps_time))

    # valids = np.nonzero(np.logical_not(gps_ang_acc == 0))
    # xc = []
    # for v in valids:
    #     xc.append((y_accel_obs[v] - y_accel_v[v] - gps_ang_vel[v]*x_vel_v[v])/gps_ang_acc[v])
    #print(np.mean(xc))

# Example usage
if __name__ == "__main__":
    cirlce_bag_file = 'Data/data_going_in_circles.bag'
    driving_bag_file = 'Data/data_driving.bag'
    analyze_imu_data(cirlce_bag_file, driving_bag_file)
