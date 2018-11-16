#include "config.h"
#include "WifiBluetooth.h"
// -----------------------------------------------------------------------------------
// configuration_focuser
const char html_configParkFocuser[] PROGMEM =
"Position: <br />"
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='Park' min='0' max='65535'>"
"<button type='submit'>Upload</button>"
" (Park position in resolution unit)"
"</form>"
"\r\n";

const char html_configMaxPositionFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='MaxPos' min='0' max='65535'>"
"<button type='submit'>Upload</button>"
" (Max position in resolution unit)"
"</form>"
"<br />\r\n";



const char html_configRotFocuser_1[] PROGMEM =
"<form action='/configuration_focuser.htm'>"
"<select name='Rot'>";


const char html_configRotFocuser_r[] PROGMEM =
"<option value ='0'>Direct</option>"
"<option selected value='1'>Reverse</option>";
const char html_configRotFocuser_d[] PROGMEM =
"<option selected value ='0'>Direct</option>"
"<option value='1'>Reverse</option>";

const char html_configRotFocuser_2[] PROGMEM =
"</select>"
"<button type='submit'>Upload</button>"
"(change this value if the focuser moves in the wrong direction)"
"</form>"
"<br />\r\n";

const char html_configLowSpeedFocuser[] PROGMEM =
"Speed & Acceleration: <br />"
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='LowSpeed' min='1' max='999'>"
"<button type='submit'>Upload</button>"
" (Minimum Slewing speed from 1 to 999)"
"</form>"
"\r\n";

const char html_configHighSpeedFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='HighSpeed' min='1' max='999'>"
"<button type='submit'>Upload</button>"
" (Maximum Slewing speed from 1 to 999)"
"</form>"
"\r\n";

const char html_configGotoAccFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='GotoAcc' min='1' max='99'>"
"<button type='submit'>Upload</button>"
" (Acceleration for goto command from 1 to 99)"
"</form>"
"\r\n";

const char html_configManAccFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='ManAcc' min='1' max='99'>"
"<button type='submit'>Upload</button>"
" (Acceleration for manual movement from 1 to 99)"
"</form>"
"\r\n";

const char html_configManDecFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='Dcc' min='1' max='99'>"
"<button type='submit'>Upload</button>"
" (Deceleration for both manual and goto from 1 to 99)"
"</form>"
"\r\n<br/>";

const char html_configResolutionFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='Res' min='1' max='512'>"
"<button type='submit'>Upload</button>"
" (Sampling in steps from 1(high resolution) to 512(low resolution))"
"</form>"
"<br/>\r\n";

const char html_configMuFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='MuF' min='4' max='128'>"
"<button type='submit'>Upload</button>"
" (Microsteps Focuser, valid value are 4, 8, 16, 32, 64, 128)"
"</form>"
"\r\n";

const char html_configLCFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='LcF' min='100' max='1600' step='10'>"
"<button type='submit'>Upload</button>"
" (Low Current Focuser, from 100mA to 1600mA)"
"</form>"
"\r\n";
const char html_configHCFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%d' type='number' name='HcF' min='100' max='1600' step='10'>"
"<button type='submit'>Upload</button>"
" (High Current Focuser, from 100mA to 1600mA)"
"</form>"
"\r\n";
const char html_configPosFocuser[] PROGMEM =
"<form method='get' action='/configuration_focuser.htm'>"
" <input value='%s' type='text' name='Fn%d' maxlength='10'>"
" <input value='%d' type='number' name='Fp%d' min='0' max='65535' step='1'>"
"<button type='submit'>Upload</button>"
" (to remove a position set an empty name)"
"</form>"
"\r\n";


#ifdef OETHS
void wifibluetooth::handleConfiguration(EthernetClient *client) {
#else
void wifibluetooth::handleConfigurationFocuser() {
#endif
  Ser.setTimeout(WebTimeout);
  serialRecvFlush();
  
  char temp[320]="";
  char temp1[80]="";
  char temp2[80]="";
  
  processConfigurationFocuserGet();

  // send a standard http response header
  String data=html_headB;
  data += html_main_cssB;
  data += html_main_css1;
  data += html_main_css2;
  data += html_main_css3;
  data += html_main_css4;
  data += html_main_css5;
  data += html_main_css6;
  data += html_main_css7;
  data += html_main_css8;
  data += html_main_cssE;
  data += html_headE;
#ifdef OETHS
  client->print(data); data="";
#endif

  data += html_bodyB;

  // get status
  mountStatus.update();
  serialRecvFlush();
  // finish the standard http response header
  data += html_onstep_header1;
  if (mountStatus.getId(temp1)) data += temp1; else data += "?";
  data += html_onstep_header2;
  if (mountStatus.getVer(temp1)) data += temp1; else data += "?";
  data += html_onstep_header3;
  data += html_links1N;
  data += html_links2N;
#if PEC_ON
  data += html_links3N;
#endif
  data += html_links4N;
  data += html_links5S;
#ifndef OETHS
  data += html_links6N;
#endif
  data += html_onstep_header4;
  
  sendCommand(":F~#", temp1);
  bool getdata = (temp1[0] == '~');
  if (getdata)
  {
    int park = (int)strtol(&temp1[1], NULL, 10);
    int maxPos = (int)strtol(&temp1[7], NULL, 10);
    int lowSpeed = (int)strtol(&temp1[13], NULL, 10);
    int highSpeed = (int)strtol(&temp1[17], NULL, 10);
    int gotoAcc = (int)strtol(&temp1[21], NULL, 10);
    int manAcc = (int)strtol(&temp1[25], NULL, 10);
    int dec = (int)strtol(&temp1[29], NULL, 10);
    sprintf_P(temp, html_configParkFocuser, park);
    data += temp;
    sprintf_P(temp, html_configMaxPositionFocuser, maxPos);
    data += temp;
    sprintf_P(temp, html_configLowSpeedFocuser, lowSpeed);
    data += temp;
    sprintf_P(temp, html_configHighSpeedFocuser, highSpeed);
    data += temp;
    sprintf_P(temp, html_configGotoAccFocuser, gotoAcc);
    data += temp;
    sprintf_P(temp, html_configManAccFocuser, manAcc);
    data += temp;
    sprintf_P(temp, html_configManDecFocuser, dec);
    data += temp;
  }
  sendCommand(":FM#", temp2);
  bool getdatamotor = (temp2[0] == 'M');
  if (getdatamotor)
  {
    int reverse = temp2[1] == '1';
    int micro = (int)strtol(&temp2[3], NULL, 10);
    int resolution = (int)strtol(&temp2[5], NULL, 10);
    int curr = 10 * (int)strtol(&temp2[9], NULL, 10);
    data += "Resolution: <br />";
    sprintf_P(temp, html_configResolutionFocuser, resolution);
    data += temp;
    data += "Rotation: <br />";
    data += FPSTR(html_configRotFocuser_1);
    data += reverse ? FPSTR(html_configRotFocuser_r) : FPSTR(html_configRotFocuser_d);
    data += FPSTR(html_configRotFocuser_2);
    data += "Motor: <br />";
    sprintf_P(temp, html_configMuFocuser, (int)pow(2., micro));
    data += temp;
    sprintf_P(temp, html_configHCFocuser, curr);
    data += temp;

  }
  sendCommand(":Fx0#", temp1);
  Serial.println(temp1);
  if (temp1[0] != 0)
  {
    if (temp1[0] == '0')
    {
      sprintf_P(temp, html_configPosFocuser, "undefined", 0, 0, 0);
      data += temp;
    }
    else if (temp1[0] == 'P')
    {
      char id[11];
      memcpy(id, &temp1[7], sizeof(id));
      int pos = (int)strtol(&temp1[1], NULL, 10);
      data += "User defined Position: <br />";
      sprintf_P(temp, html_configPosFocuser, id, 0, pos, 0);
      data += temp;
    }
  }


  


#ifdef OETHS
  client->print(data); data="";
#endif

  strcpy(temp,"</div></div></body></html>");
  data += temp;

#ifdef OETHS
  client->print(data); data="";
#else
  server.send(200, "text/html",data);
#endif
}

void wifibluetooth::processConfigurationFocuserGet() {
  String v;
  int i;
  float f;
  char temp[20]="";

  v = server.arg("Park");
  if (v != "") {
    if ((atof2((char*)v.c_str(), &f)) && ((f >= 0) && (f <= 65535))) {
      sprintf(temp, ":F0 %05d#", (int)f);
      Ser.print(temp);
    }
  }

  v = server.arg("MaxPos");
  if (v != "") {
    if ((atof2((char*)v.c_str(), &f)) && ((f >= 0) && (f <= 65535))) {
      sprintf(temp, ":F1 %05d#", (int)f);
      Ser.print(temp);
    }
  }

  v = server.arg("LowSpeed");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 1) && (i <= 999))) {
      sprintf(temp, ":F2 %d#", i);
      Ser.print(temp);
    }
  }

  v = server.arg("HighSpeed");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 1) && (i <= 999))) {
      sprintf(temp, ":F3 %d#", i);
      Ser.print(temp);
    }
  }

  v = server.arg("GotoAcc");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 1) && (i <= 99))) {
      sprintf(temp, ":F4 %d#", i);
      Ser.print(temp);
    }
  }
  v = server.arg("ManAcc");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 1) && (i <= 99))) {
      sprintf(temp, ":F5 %d#", i);
      Ser.print(temp);
    }
  }
  v = server.arg("Dcc");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 1) && (i <= 99))) {
      sprintf(temp, ":F6 %d#", i);
      Ser.print(temp);
    }
  }
  v = server.arg("Rot");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 0) && (i <= 1))) {
      sprintf(temp, ":F7 %d#", i);
      Ser.print(temp);
    }
  }
  v = server.arg("Res");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 1) && (i <= 512))) {
      sprintf(temp, ":F8 %d#", i);
      Ser.print(temp);
    }
  }
  v = server.arg("MuF");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 4) && (i <= 128))) {
      sprintf(temp, ":Fm %d#", (int)log2(i));
      Ser.print(temp);
    }
  }

  v = server.arg("HcF");
  if (v != "") {
    if ((atoi2((char*)v.c_str(), &i)) && ((i >= 100) && (i <= 1600))) {
      sprintf(temp, ":Fc %d#", i / 10);
      Ser.print(temp);
    }
  }
  Ser.flush();
  serialRecvFlush();
}

