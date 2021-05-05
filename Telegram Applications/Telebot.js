var token = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
var telegramUrl = "https://api.telegram.org/bot" + token;
var app_name = "sheet-bot";
var webAppUrl = "https://script.google.com/macros/s/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/exec";

function getOpponent(user){
  var ss = SpreadsheetApp.openById("1hk_xMYXtFSNZEolbfYeUlCgCNy-oLYNv4hrerqK2WCs");
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('BoG Ladder');
  var matchups = sheet.getRange(1,1,39,10);
  for(i=1; i < matchups.getHeight(); ++i){
    if(sheet.getRange(i,10).getValue().toString().toLowerCase() == user.toLowerCase()){
      return sheet.getRange(i,10).getValue() + ', your opponent against ' + sheet.getRange(1,7).getValue() + ' is ' + sheet.getRange(i,8).getValue() + ' and you will be ' + sheet.getRange(i,9).getValue() + ' against them';
    }
  }
  sheet = ss.getSheetByName('BoL Ladder');
  var matchups = sheet.getRange(1,1,39,10);
  for(i=1; i < matchups.getHeight(); ++i){
    if(sheet.getRange(i,10).getValue().toString().toLowerCase() == user.toLowerCase()){
      return sheet.getRange(i,10).getValue() + ', your opponent against ' + sheet.getRange(1,7).getValue() + ' is ' + sheet.getRange(i,8).getValue() + ' and you will be ' + sheet.getRange(i,9).getValue() + ' against them';
    }
  }
  sheet = ss.getSheetByName('TGB Ladder');
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
  var plays = sheet.getRange(2,2,224,3);
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
  var ss = SpreadsheetApp.openById("1hk_xMYXtFSNZEolbfYeUlCgCNy-oLYNv4hrerqK2WCs");
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('Brotherhood of Goonz');
  if(league == "bog"){
    //return "correct";
    sheet = ss.getSheetByName('Brotherhood of Goonz');
  }
  if(league == "bol"){
    sheet = ss.getSheetByName('Band of Legends');
  }
  if(league == "tgb"){
    sheet = ss.getSheetByName('The Goonz Brothers');
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
  var ss = SpreadsheetApp.openById("1hk_xMYXtFSNZEolbfYeUlCgCNy-oLYNv4hrerqK2WCs");
  SpreadsheetApp.setActiveSpreadsheet(ss);
  var sheet = ss.getSheetByName('Brotherhood of Goonz');
  if(league == "bog"){
    sheet = ss.getSheetByName('Brotherhood of Goonz');
  }
  else if(league == "bol"){
    sheet = ss.getSheetByName('Band of Legends');
  }
  else if(league == "tgb"){
    sheet = ss.getSheetByName('The Goonz Brothers');
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

  if(input.substr(0,input.indexOf(' ')).toLowerCase() == "new"){
    sheet.insertColumnBefore(23);
  }
  
  if(input.substr(0,input.indexOf(' ')).toLowerCase() == "def"){
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
  return 1;
}
