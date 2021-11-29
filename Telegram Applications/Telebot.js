var token = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
var telegramUrl = "https://api.telegram.org/bot" + token;
var app_name = "sheet-bot";
var webAppUrl = "https://script.google.com/macros/s/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/exec";

var ssid = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

function register(input){
  var league = input.substr(0,input.indexOf(' ')).toLowerCase();
  console.log(league);
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  input = input.substr(input.indexOf(' ')+1,input.length);
  var name = input;
  for(i = 6; i < 38; i++){
    if(sheet.getRange(i,4).getValue() == name || sheet.getRange(i + 34,4).getValue() == name){
      return "This user is already on this sheet";
    }
  }
  for(i = 6; i < 37; i++){
    if(sheet.getRange(i,4).getValue() == ""){
      sheet.getRange(i,4).setValue(name);
      break;
    }
  }
  for(i = 90; i < 122; i++){
    if(sheet.getRange(i,4).getValue() == ""){
      sheet.getRange(i,4).setValue(name);
      break;
    }
  }
  return name + " has been registered on the sheet";
}

function guide(id){
  var text = "Bot Guide:%0A%0A/register [league abbrv] [ign]%0AWill put your ign on the sheet if it is not there already.%0ANote: DO NOT use this command if you were in the league previously. Please ask an admin to move your scores from the inactive section of that league's tab back into the active section%0A%0A/setup [league abbrv] [opposing league name]: [opp rank] [our rank]%0AWill set up today's matchup%0ANote: Make sure to use a colon after the opposing league name%0A%0A/result [league] [result] [our drives] [our score] [opp drives] [opp score] [days ago]%0AWill input the results of the matchup%0ANote: result will be WIN LOSS or TIE%0ANote: days ago will input the result of the match for the column that many days ago%0A%0A/newday%0AWill set up a new day for every league. This function runs automatically every day%0A%0A/average [ign] [average type]%0AWill return the specified average of the specified player%0ANote: This will pull the cross-league average. Average type will be 3,7,10,14,30, or yearly%0A%0A/leagueaverage [league] [ign] [average type]%0AWill return the specified average of the specified player in the specified league%0ANote: Average type will be 3,7,14,30,yearly, and 100 where 100 is the 10 day for top 100 matches. If the league is mgl 50 is for the 10 day of top 50 matches and if the league is bob 10 is just 10 day%0A%0A";
  sendText(id,text);
  return "/ovr [league] [ign] [off ovr] [def ovr] [total ovr]%0AWill input the user's team strength%0ANote: DO NOT USE SLASHES BETWEEN THE VALUES! Slashes are automatically added in the response message, please separate the values with spaces%0A%0A/opponent [league] [ign]%0AOn a day where the ladder on this sheet is used, this will return the user's opponent%0ANote: As of right now please don't use this command, since it's prone to being inaccurate. Please just use the %0Aladders posted%0A%0A/update [league]%0AWill return the match status for the specified league%0ANote: Ask an admin to enter all the scores if this command is to work properly%0A%0A/score%0AThis command has many parts. Please type /scoreguide to see the guide for this command.";

}

function scoreguide(){
  return "Parts of the /score command:%0ANote: every time you use the score command it will start with /score [league]%0A%0AInput the opponent's stats:%0A/score [league] opp [opp score] [opp drives]%0A%0AInput your defensive score:%0A/score [league] def [ign] [score] [days ago]%0A%0AInput your score:%0A/score [league] [ign] [score] [days ago]%0A%0AInput the league's defensive points (pick sixes, safeties, etc.)%0A/score [league] defscore [points]%0A%0AInput the league's held tds:%0A/score [league] holds [held tds]";
}

function setup(input){
  var league = input.substr(0,input.indexOf(' ')).toLowerCase();
  console.log(league);
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  input = input.substr(input.indexOf(' ')+1,input.length);
  console.log(input);
  opponent = input.substr(0, (input.indexOf(':')>=0)?input.indexOf(':') : input.length);
  input = input.substr(input.indexOf(':')+2,input.length);
  opprank = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  input = input.substr(input.indexOf(' ')+1,input.length);
  ourrank = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  daysago = 0;
  input = input.substr((input.indexOf(' ')>=0)?input.indexOf(' ')+1 : input.length,input.length);
  if(input.length > 0){
    daysago = input;
  }
  sheet.getRange(1,23+daysago).setValue(opponent);
  sheet.getRange(2,23+daysago).setValue(opprank);
  sheet.getRange(3,23+daysago).setValue(ourrank);
  output = "Match has been set up. Good luck against Rank " + opprank + " " + opponent;
  return output;
}

function result(input){
  var league = input.substr(0,input.indexOf(' ')).toLowerCase();
  console.log(league);
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  input = input.substr(input.indexOf(' ')+1,input.length);
  console.log(input);
  endresult = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  input = input.substr(input.indexOf(' ')+1,input.length);
  ourdrives = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  input = input.substr(input.indexOf(' ')+1,input.length);
  ourscore = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  input = input.substr(input.indexOf(' ')+1,input.length);
  theirdrives = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  input = input.substr(input.indexOf(' ')+1,input.length);
  theirscore = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  daysago = 0;
  input = input.substr((input.indexOf(' ')>=0)?input.indexOf(' ')+1 : input.length,input.length);
  if(input.length > 0){
    daysago = input;
  }
  daysago = parseInt(daysago);
  sheet.getRange(5,23+daysago).setValue(endresult.toUpperCase());
  sheet.getRange(73,23+daysago).setValue(ourdrives);
  sheet.getRange(76,23+daysago).setValue(ourscore);
  sheet.getRange(77,23+daysago).setValue(theirdrives);
  sheet.getRange(80,23+daysago).setValue(theirscore);
  return "Inputted Match Results";
}

function newday(){
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  sheet.insertColumnBefore(23);
  sheet.getRange(4,23).setValue("=X4+1");
  sheet.getRange(5,23).setValue("=if(W76>INDIRECT(\"E79\"), \"CLINCHED!\", if(W80>indirect(\"E75\"), \"LOST\", IF(INDIRECT(\"E81\")>0,\"AHEAD\", if(indirect(\"E81\")=0, \"TIED\", \"BEHIND\"))))");
  sheet.getRange(73,23).setValue("=iferror(counta(W6:W67)*3, W67)");
  sheet.getRange(74,23).setValue("=iferror((W76+(indirect(\"J73\")*6)+(INDIRECT(\"J74\")*3))/W73,0)");
  sheet.getRange(75,23).setValue("=iferror(average(W8:W37),0)");
  sheet.getRange(76,23).setValue("=SUM((ARRAYFORMULA(IF(NOT(ISBLANK(INDIRECT(\"w6:w37\"))),VALUE(regexreplace(TO_TEXT(INDIRECT(\"w6:w37\")),\"f\",\"\")),))))+indirect(\"H73\")");
  sheet.getRange(77,23).setValue("0");
  sheet.getRange(78,23).setValue("=iferror((W80+indirect(\"J77\")*6+indirect(\"J78\")*3)/(W77+indirect(\"J77\")+indirect(\"J78\")),0)");
  sheet.getRange(79,23).setValue("=iferror(W80/(W77/3), 0)");
  sheet.getRange(80,23).setValue("0");
  sheet.getRange(81,23).setValue("=Minus (W76,W80)");
  sheet.getRange(82,23).setValue("=iferror(counta('MGL'!W6:W37))");

  for(i = 159; i <= 190; i++){
    sheet.getRange(i,23).setValue("=IF(ISBLANK(IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D6:ZZ37\"),COLUMN()-3,FALSE),)),\"\",VALUE(regexreplace(TO_TEXT(IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D6:ZZ37\"),COLUMN()-3,FALSE),)),\"f\",\"\"))-IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D90:ZZ121\"),COLUMN()-3,FALSE),))")
  }

  sheet = ss.getSheetByName('Band of Brothers');
  sheet.insertColumnBefore(23);
  sheet.getRange(4,23).setValue("=X4+1");
  sheet.getRange(5,23).setValue("=if(W76>INDIRECT(\"E79\"), \"CLINCHED!\", if(W80>indirect(\"E75\"), \"LOST\", IF(INDIRECT(\"E81\")>0,\"AHEAD\", if(indirect(\"E81\")=0, \"TIED\", \"BEHIND\"))))");
  sheet.getRange(73,23).setValue("=iferror(counta(W6:W67)*3, W67)");
  sheet.getRange(74,23).setValue("=iferror((W76+(indirect(\"J73\")*6)+(INDIRECT(\"J74\")*3))/W73,0)");
  sheet.getRange(75,23).setValue("=iferror(average(W8:W37),0)");
  sheet.getRange(76,23).setValue("=SUM((ARRAYFORMULA(IF(NOT(ISBLANK(INDIRECT(\"w6:w37\"))),VALUE(regexreplace(TO_TEXT(INDIRECT(\"w6:w37\")),\"f\",\"\")),))))+indirect(\"H73\")");
  sheet.getRange(77,23).setValue("0");
  sheet.getRange(78,23).setValue("=iferror((W80+indirect(\"J77\")*6+indirect(\"J78\")*3)/(W77+indirect(\"J77\")+indirect(\"J78\")),0)");
  sheet.getRange(79,23).setValue("=iferror(W80/(W77/3), 0)");
  sheet.getRange(80,23).setValue("0");
  sheet.getRange(81,23).setValue("=Minus (W76,W80)");
  sheet.getRange(82,23).setValue("=iferror(counta('Band of Brothers'!W6:W37))");

  for(i = 159; i <= 190; i++){
    sheet.getRange(i,23).setValue("=IF(ISBLANK(IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D6:ZZ37\"),COLUMN()-3,FALSE),)),\"\",VALUE(regexreplace(TO_TEXT(IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D6:ZZ37\"),COLUMN()-3,FALSE),)),\"f\",\"\"))-IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D90:ZZ121\"),COLUMN()-3,FALSE),))")
  }

  sheet = ss.getSheetByName('OLD B');
  sheet.insertColumnBefore(23);
  sheet.getRange(4,23).setValue("=X4+1");
  sheet.getRange(5,23).setValue("=if(W76>INDIRECT(\"E79\"), \"CLINCHED!\", if(W80>indirect(\"E75\"), \"LOST\", IF(INDIRECT(\"E81\")>0,\"AHEAD\", if(indirect(\"E81\")=0, \"TIED\", \"BEHIND\"))))");
  sheet.getRange(73,23).setValue("=iferror(counta(W6:W67)*3, W67)");
  sheet.getRange(74,23).setValue("=iferror((W76+(indirect(\"J73\")*6)+(INDIRECT(\"J74\")*3))/W73,0)");
  sheet.getRange(75,23).setValue("=iferror(average(W8:W37),0)");
  sheet.getRange(76,23).setValue("=SUM((ARRAYFORMULA(IF(NOT(ISBLANK(INDIRECT(\"w6:w37\"))),VALUE(regexreplace(TO_TEXT(INDIRECT(\"w6:w37\")),\"f\",\"\")),))))+indirect(\"H73\")");
  sheet.getRange(77,23).setValue("0");
  sheet.getRange(78,23).setValue("=iferror((W80+indirect(\"J77\")*6+indirect(\"J78\")*3)/(W77+indirect(\"J77\")+indirect(\"J78\")),0)");
  sheet.getRange(79,23).setValue("=iferror(W80/(W77/3), 0)");
  sheet.getRange(80,23).setValue("0");
  sheet.getRange(81,23).setValue("=Minus (W76,W80)");
  sheet.getRange(82,23).setValue("=iferror(counta('Band of Brothers'!W6:W37))");

  for(i = 159; i <= 190; i++){
    sheet.getRange(i,23).setValue("=IF(ISBLANK(IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D6:ZZ37\"),COLUMN()-3,FALSE),)),\"\",VALUE(regexreplace(TO_TEXT(IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D6:ZZ37\"),COLUMN()-3,FALSE),)),\"f\",\"\"))-IFERROR(VLOOKUP(INDIRECT(\"D"+ i.toString() + "\"),indirect(\"D90:ZZ121\"),COLUMN()-3,FALSE),))")
  }

  var sheet = ss.getSheetByName('Cross League Scoring');
  sheet.insertColumnAfter(18);
  sendText(-1001219448091,"New day inputted");
  return "New day inputted";
}

function average(input){
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('Cross League Scoring');
  console.log(input);
  var people = sheet.getRange(2,1,52,20);
  var user = input.substr(0,(input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  if(user == "" || user == " "){
    return "incorrect user";
  }
  console.log(user);
  input = input.substr(input.indexOf(' ')+1,input.length);
  type = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  type = type.toLowerCase();
  var col;
  if(type == "10"){
    col = 7;
  }
  else if(type == "3"){
    col = 13;
  }
  else if(type == "7"){
    col = 14;
  }
  else if(type == "14"){
    col = 15;
  }
  else if(type == "30"){
    col = 16;
  }
  else if(type == "yearly"){
    col = 17;
  }
  else{
    return "incorrect average type";
  }
  
  for(i=2; i < 2+people.getHeight(); ++i){
    if(sheet.getRange(i,1).getValue().toString().toLowerCase() == user.toLowerCase()){
      return user + " has a " + type + (type == "yearly" ? "" : " day") + " average of " + sheet.getRange(i,col).getValue().toFixed(2);
    }
  }
  return "incorrect ign";
}

function leagueaverage(input){
  var league = input.substr(0,input.indexOf(' ')).toLowerCase();
  console.log(league);
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  input = input.substr(input.indexOf(' ')+1,input.length);
  console.log(input);
  var people = sheet.getRange(6,4,32,20);
  var user = input.substr(0,(input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  if(user == "" || user == " "){
    return "incorrect user";
  }
  console.log(user);
  input = input.substr(input.indexOf(' ')+1,input.length);
  type = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
  type = type.toLowerCase();
  var col;
  if((type == "50" && league == "mgl") || type == "10"){
    col = 10;
  }
  else if(type == "100"){
    col = 11;
  }
  else if(type == "3"){
    col = 18;
  }
  else if(type == "7"){
    col = 19;
  }
  else if(type == "14"){
    col = 20;
  }
  else if(type == "30"){
    col = 21;
  }
  else if(type == "yearly"){
    col = 22;
  }
  else{
    return "incorrect average type";
  }
  
  for(i=6; i < 6+people.getHeight(); ++i){
    if(sheet.getRange(i,4).getValue().toString().toLowerCase() == user.toLowerCase()){
      return user + " has a " + (type == "50" ? "top 50 10" : (type == "100" ? "top 100 10" : type)) + (type == "yearly" ? "" : " day") + " average of " + sheet.getRange(i,col).getValue().toFixed(2);
    }
  }
  return "incorrect ign";
}

function ovr(input){
  var league = input.substr(0,input.indexOf(' ')).toLowerCase();
  console.log(league);
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  input = input.substr(input.indexOf(' ')+1,input.length);
  console.log(input);
  var people = sheet.getRange(6,4,32,20);
    var user = input.substr(0,(input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    if(user == "" || user == " "){
      return "incorrect user";
    }
    console.log(user);
    input = input.substr(input.indexOf(' ')+1,input.length);
    off = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    input = input.substr(input.indexOf(' ')+1,input.length);
    def = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    input = input.substr(input.indexOf(' ')+1,input.length);
    total = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    for(i=6; i < 6+people.getHeight(); ++i){
      if(sheet.getRange(i,4).getValue().toString().toLowerCase() == user.toLowerCase()){
        sheet.getRange(i,5).setValue(off);
        sheet.getRange(i,6).setValue(def);
        sheet.getRange(i,7).setValue(total);
        return user + " has inputted a team of " + off + " off / " + def + " def / " + total + " total ovr";
      }
    }
    return "incorrect ign";
}

function getOpponent(user){
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL Ladder');
  var matchups = sheet.getRange(1,1,39,10);
  for(i=1; i < matchups.getHeight(); ++i){
    if(sheet.getRange(i,10).getValue().toString().toLowerCase() == user.toLowerCase()){
      return sheet.getRange(i,10).getValue() + ', your opponent against ' + sheet.getRange(1,7).getValue() + ' is ' + sheet.getRange(i,8).getValue() + ' and you will be ' + sheet.getRange(i,9).getValue() + ' against them';
    }
  }
  sheet = ss.getSheetByName('bob Ladder');
  var matchups = sheet.getRange(1,1,39,10);
  for(i=1; i < matchups.getHeight(); ++i){
    if(sheet.getRange(i,10).getValue().toString().toLowerCase() == user.toLowerCase()){
      return sheet.getRange(i,10).getValue() + ', your opponent against ' + sheet.getRange(1,7).getValue() + ' is ' + sheet.getRange(i,8).getValue() + ' and you will be ' + sheet.getRange(i,9).getValue() + ' against them';
    }
  }
}

function getCounter(play){
  var ss = SpreadsheetApp.openById("1UB48hAut-Fg493WvY00GIE-VPWSGzoVGBOzQXxM-4sE");
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('Counters');
  var plays = sheet.getRange(2,2,225,3);
  for(i = 1; i < plays.getHeight(); ++i){
    if(sheet.getRange(i,2).getValue().toString().toLowerCase() == play.toLowerCase()){
      return play + ' is countered with ' + sheet.getRange(i,3).getValue();
    }
  }
  return 'Play not found';
}

function doGet(e) {
  return HtmlService.createHtmlOutput("Hi there");
}

function getUpdate(league){
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  var score = sheet.getRange(76,23).getValue();
  var drives = sheet.getRange(73,23).getValue();
  var ppd = sheet.getRange(74,23).getValue();
  var projscore = sheet.getRange(73,12).getValue();
  var oppscore = sheet.getRange(80,23).getValue();
  var oppdrives = sheet.getRange(77,23).getValue();
  var oppppd = sheet.getRange(78,23).getValue();
  var oppprojscore = sheet.getRange(77,12).getValue();
  var pointstoclinch = sheet.getRange(82,5).getValue();
  var heldtds = sheet.getRange(73,10).getValue();
  var held4ths = sheet.getRange(75,10).getValue();
  var oppheldtds = sheet.getRange(77,10).getValue();
  var oppheld4ths = sheet.getRange(79,10).getValue();
  var us = "US:%0AScore: " + score + " %0ADrives: "+ drives + " %0APPD: "  + ppd.toFixed(2) + " %0AProjected Score: " + Math.round(projscore)+ "%0AHeld TDs: " + heldtds + "%0AHeld 4ths: " + held4ths + " %0A%0ATHEM: %0AScore: " + oppscore + " %0ADrives: " + oppdrives + " %0APPD: " + oppppd.toFixed(2) + " %0AProjected Score: " + Math.round(oppprojscore) + "%0AHeld TDs: " + oppheldtds + "%0AHeld 4ths: " + oppheld4ths + " %0A%0APoints to Clinch: " + pointstoclinch;
  console.log(us);
  return us;
}

function score(input){
  var league = input.substr(0,input.indexOf(' ')).toLowerCase();
  console.log(league);
  var ss = SpreadsheetApp.openById(ssid);
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('MGL');
  if(league == "mgl"){
    sheet = ss.getSheetByName('MGL');
  }
  else if(league == "bob"){
    sheet = ss.getSheetByName('Band of Brothers');
  }
  else if(league == "obob"){
    sheet = ss.getSheetByName('OLD B');
  }
  else{
    return "incorrect league";
  }
  input = input.substr(input.indexOf(' ')+1,input.length);
  console.log(input);
  if(input.substr(0,input.indexOf(' ')).toLowerCase() == "opp"){
    input = input.substr(input.indexOf(' ')+1,input.length);
    console.log(input);
    oppscore = input.substr(0, input.indexOf(' '));
    input = input.substr(input.indexOf(' '),input.length);
    oppdrives = input.substr(input.indexOf(' ')+1,input.length);
    if(oppscore != "" && oppscore != " " && oppdrives != "" && oppdrives != " "){
      sheet.getRange(80,23).setValue(oppscore);
      sheet.getRange(77,23).setValue(oppdrives);
      return "inputted opponent's score";
    }
    return "inccorect format for opponent's score";
  }

  if(input.substr(0,input.indexOf(' ')).toLowerCase() == "def"){
    input = input.substr(input.indexOf(' ')+1,input.length);
    var people = sheet.getRange(90,4,32,20);
    var user = input.substr(0,(input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    if(user == "" || user == " "){
      return "incorrect user";
    }
    console.log(user);
    input = input.substr(input.indexOf(' ')+1,input.length);
    userscore = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    daysago = 0;
    input = input.substr((input.indexOf(' ')>=0)?input.indexOf(' ')+1 : input.length,input.length);
    if(input.length > 0){
      daysago = input;
    }
    daysago = parseInt(daysago);
    for(i=90; i < 90+people.getHeight(); ++i){
      if(sheet.getRange(i,4).getValue().toString().toLowerCase() == user.toLowerCase()){
        sheet.getRange(i,23+daysago).setValue(userscore);
        return user + " has inputted a defensive score of " + userscore + ((daysago > 0)? (" for " + daysago + " day(s) ago"): "");
      }
    }
    return "incorrect ign";
  }
  if(input.substr(0,input.indexOf(' ')).toLowerCase() == "defscore"){
    defpoints = input.substr(input.indexOf(' ')+1,input.length);
    sheet.getRange(73,8).setValue(defpoints);
    return "inputted defensive points";
  }
  if(input.substr(0,input.indexOf(' ')).toLowerCase() == "holds"){
    holds = input.substr(input.indexOf(' ')+1,input.length);
    sheet.getRange(73,10).setValue(holds);
      return "inputted holds";
  }
  else{
    var people = sheet.getRange(6,4,32,20);
    var user = input.substr(0,(input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    if(user == "" || user == " "){
      return "incorrect user";
    }
    console.log(user);
    input = input.substr(input.indexOf(' ')+1,input.length);
    userscore = input.substr(0, (input.indexOf(' ')>=0)?input.indexOf(' ') : input.length);
    daysago = 0;
    input = input.substr((input.indexOf(' ')>=0)?input.indexOf(' ')+1 : input.length,input.length);
    if(input.length > 0){
      daysago = input;
    }
    daysago = parseInt(daysago);
    for(i=6; i < 6+people.getHeight(); ++i){
      if(sheet.getRange(i,4).getValue().toString().toLowerCase() == user.toLowerCase()){
        sheet.getRange(i,23+daysago).setValue(userscore);
        return user + " has inputted a score of " + userscore + ((daysago > 0)? (" for " + daysago + " day(s) ago"): "");
      }
    }
    return "incorrect ign";
  }
  return "did not input correctly";
}

function getMe() {
  var url = telegramUrl + "/getMe";
  var response = UrlFetchApp.fetch(url);
  Logger.log(response.getContentText());
}

function setWebhook() {
  var url = telegramUrl + "/setWebhook?url=" + webAppUrl;
  var response = UrlFetchApp.fetch(url);
  Logger.log(response.getContentText());
}

function sendText(id,text) {
  var url = telegramUrl + "/sendMessage?chat_id=" + id + "&text=" + text;
  var response = UrlFetchApp.fetch(url);
  Logger.log(response.getContentText());
}

function doPost(e){
  var data = JSON.parse(e.postData.contents);
  var text = data.message.text;
  var id = data.message.chat.id;
  if(text.substr(0,text.indexOf(' ')) == '/opponent'){
    var output = getOpponent(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/counter'){
    var output = getCounter(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/update'){
    var output = getUpdate(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/score'){
    var output = score(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/ovr'){
    var output = ovr(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/average'){
    var output = average(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/leagueaverage'){
    var output = leagueaverage(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/result'){
    var output = result(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/setup'){
    var output = setup(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  if(text == '/newday'){
    var output = newday();
    sendText(id,output);
  }
  if(text == '/guide'){
    var output = guide(id);
    sendText(id,output);
  }
  if(text == '/scoreguide'){
    var output = scoreguide();
    sendText(id,output);
  }
  if(text.substr(0,text.indexOf(' ')) == '/register'){
    var output = register(text.substr(text.indexOf(' ')+1));
    sendText(id,output);
  }
  return 1;
}