#include <ACS712.h>

ACS712 ampereIn(PA1, 5000, 1024, 66);
ACS712 ampereOut(PA3, 5000, 1024, 66);
const int pwmDM = PA4;
const int inputanVoltPSU = PA0;
const int outputVoltSEPIC = PA2;
const float revteg = 5.0;
float outputVolt;
float inputanVolt;
float arusIn;
float fixArusin = arusIn * 0.001;
float arusOut;
float fixArusout = arusOut * 0.001;

void setup() {
  Serial.begin(9600);
}

void loop() {
  arusIn = ampereIn.mA_DC(10);
  arusOut = ampereOut.mA_DC(10);
  fixArusin = arusIn * 0.001;
  fixArusout = arusOut * 0.001;
  int PSU = analogRead(inputanVoltPSU);
  inputanVolt = (float)(PSU * revteg) / 1023.0;
  if (inputanVolt > 0.5) {
    inputanVolt -= 0.425;
    if (inputanVolt > 1) {
      inputanVolt -= 0.425;
      if (inputanVolt > 2) {
        inputanVolt -= 0.825;
        if (inputanVolt > 3) {
          inputanVolt -= 0.425;
          if (inputanVolt > 4) {
            inputanVolt -= 0.250;
            if (inputanVolt > 5) {
              inputanVolt -= 0.250;
              if (inputanVolt > 6) {
                inputanVolt -= 0.650;
                if (inputanVolt > 7) {
                  inputanVolt -= 0.425;
                  if (inputanVolt > 8) {
                    inputanVolt -= 0.425;
                    if (inputanVolt > 9) {
                      inputanVolt -= 0.425;
                      if (inputanVolt > 10) {
                        inputanVolt -= 0.425;
                        if (inputanVolt > 11) {
                          inputanVolt -= 0.425;
                          if (inputanVolt > 12) {
                            inputanVolt -= 0.425;
                            if (inputanVolt > 13) {
                              inputanVolt -= 0.425;
                              if (inputanVolt > 14) {
                                inputanVolt -= 0.425;
                                if (inputanVolt > 15) {
                                  inputanVolt -= 0.425;
                                  if (inputanVolt > 16) {
                                    inputanVolt -= 0.425;
                                    if (inputanVolt > 17) {
                                      inputanVolt -= 0.425;
                                      if (inputanVolt > 18) {
                                        inputanVolt -= 0.425;
                                        if (inputanVolt > 19) {
                                          inputanVolt -= 0.425;
                                          if (inputanVolt > 20) {
                                            inputanVolt -= 0.425;
                                            if (inputanVolt > 21) {
                                              inputanVolt -= 0.425;
                                              if (inputanVolt > 22) {
                                                inputanVolt -= 0.425;
                                                if (inputanVolt > 23) {
                                                  inputanVolt -= 0.425;
                                                  if (inputanVolt > 24) {
                                                    inputanVolt -= 0.425;
                                                    if (inputanVolt > 25) {
                                                      inputanVolt -= 0.425;
                                                      if (inputanVolt > 26) {
                                                        inputanVolt -= 0.425;
                                                        if (inputanVolt > 27) {
                                                          inputanVolt -= 0.425;
                                                          if (inputanVolt > 28) {
                                                            inputanVolt -= 0.425;
                                                            if (inputanVolt > 29) {
                                                              inputanVolt -= 0.425;
                                                              if (inputanVolt > 30) {
                                                                inputanVolt -= 0.425;
                                                                if (inputanVolt > 31) {
                                                                  inputanVolt -= 0.425;
                                                                  if (inputanVolt > 32) {
                                                                    inputanVolt -= 0.425;
                                                                    if (inputanVolt > 33) {
                                                                      inputanVolt -= 0.425;
                                                                      if (inputanVolt > 34) {
                                                                        inputanVolt -= 0.425;
                                                                        if (inputanVolt > 35) {
                                                                          inputanVolt -= 0.425;
                                                                          if (inputanVolt > 36) {
                                                                            inputanVolt -= 0.425;
                                                                            if (inputanVolt > 37) {
                                                                              inputanVolt -= 0.425;
                                                                              if (inputanVolt > 38) {
                                                                                inputanVolt -= 0.425;
                                                                                if (inputanVolt > 39) {
                                                                                  inputanVolt -= 0.425;
                                                                                  if (inputanVolt > 40) {
                                                                                    inputanVolt -= 0.425;
                                                                                    if (inputanVolt > 41) {
                                                                                      inputanVolt -= 0.425;
                                                                                      if (inputanVolt > 42) {
                                                                                        inputanVolt -= 0.425;
                                                                                        if (inputanVolt > 43) {
                                                                                          inputanVolt -= 0.425;
                                                                                          if (inputanVolt > 44) {
                                                                                            inputanVolt -= 0.425;
                                                                                            if (inputanVolt > 45) {
                                                                                              inputanVolt -= 0.425;
                                                                                              if (inputanVolt > 46) {
                                                                                                inputanVolt -= 0.425;
                                                                                                if (inputanVolt > 47) {
                                                                                                  inputanVolt -= 0.425;
                                                                                                  if (inputanVolt > 48) {
                                                                                                    inputanVolt -= 0.425;
                                                                                                    if (inputanVolt > 49) {
                                                                                                      inputanVolt -= 0.425;
                                                                                                      if (inputanVolt > 50) {
                                                                                                        inputanVolt -= 0.425;
                                                                                                      }
                                                                                                    }
                                                                                                  }
                                                                                                }
                                                                                              }
                                                                                            }
                                                                                          }
                                                                                        }
                                                                                      }
                                                                                    }
                                                                                  }
                                                                                }
                                                                              }
                                                                            }
                                                                          }
                                                                        }
                                                                      }
                                                                    }
                                                                  }
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  
  int VOUT = analogRead(outputVoltSEPIC);
  outputVolt = (float)(VOUT * revteg) / 1023.0;
  if (outputVolt > 0.5) {
    outputVolt -= 0.425;
    if (outputVolt > 1) {
      outputVolt -= 0.425;
      if (outputVolt > 2) {
        outputVolt -= 0.825;
        if (outputVolt > 3) {
          outputVolt -= 0.425;
          if (outputVolt > 4) {
            outputVolt -= 0.250;
            if (outputVolt > 5) {
              outputVolt -= 0.250;
              if (outputVolt > 6) {
                outputVolt -= 0.650;
                if (outputVolt > 7) {
                  outputVolt -= 0.425;
                  if (outputVolt > 8) {
                    outputVolt -= 0.425;
                    if (outputVolt > 9) {
                      outputVolt -= 0.425;
                      if (outputVolt > 10) {
                        outputVolt -= 0.425;
                        if (outputVolt > 11) {
                          outputVolt -= 0.425;
                          if (outputVolt > 12) {
                            outputVolt -= 0.425;
                            if (outputVolt > 13) {
                              outputVolt -= 0.425;
                              if (outputVolt > 14) {
                                outputVolt -= 0.425;
                                if (outputVolt > 15) {
                                  outputVolt -= 0.425;
                                  if (outputVolt > 16) {
                                    outputVolt -= 0.425;
                                    if (outputVolt > 17) {
                                      outputVolt -= 0.425;
                                      if (outputVolt > 18) {
                                        outputVolt -= 0.425;
                                        if (outputVolt > 19) {
                                          outputVolt -= 0.425;
                                          if (outputVolt > 20) {
                                            outputVolt -= 0.425;
                                            if (outputVolt > 21) {
                                              outputVolt -= 0.425;
                                              if (outputVolt > 22) {
                                                outputVolt -= 0.425;
                                                if (outputVolt > 23) {
                                                  outputVolt -= 0.425;
                                                  if (outputVolt > 24) {
                                                    outputVolt -= 0.425;
                                                    if (outputVolt > 25) {
                                                      outputVolt -= 0.425;
                                                      if (outputVolt > 26) {
                                                        outputVolt -= 0.425;
                                                        if (outputVolt > 27) {
                                                          outputVolt -= 0.425;
                                                          if (outputVolt > 28) {
                                                            outputVolt -= 0.425;
                                                            if (outputVolt > 29) {
                                                              outputVolt -= 0.425;
                                                              if (outputVolt > 30) {
                                                                outputVolt -= 0.425;
                                                                if (outputVolt > 31) {
                                                                  outputVolt -= 0.425;
                                                                  if (outputVolt > 32) {
                                                                    outputVolt -= 0.425;
                                                                    if (outputVolt > 33) {
                                                                      outputVolt -= 0.425;
                                                                      if (outputVolt > 34) {
                                                                        outputVolt -= 0.425;
                                                                        if (outputVolt > 35) {
                                                                          outputVolt -= 0.425;
                                                                          if (outputVolt > 36) {
                                                                            outputVolt -= 0.425;
                                                                            if (outputVolt > 37) {
                                                                              outputVolt -= 0.425;
                                                                              if (outputVolt > 38) {
                                                                                outputVolt -= 0.425;
                                                                                if (outputVolt > 39) {
                                                                                  outputVolt -= 0.425;
                                                                                  if (outputVolt > 40) {
                                                                                    outputVolt -= 0.425;
                                                                                    if (outputVolt > 41) {
                                                                                      outputVolt -= 0.425;
                                                                                      if (outputVolt > 42) {
                                                                                        outputVolt -= 0.425;
                                                                                        if (outputVolt > 43) {
                                                                                          outputVolt -= 0.425;
                                                                                          if (outputVolt > 44) {
                                                                                            outputVolt -= 0.425;
                                                                                            if (outputVolt > 45) {
                                                                                              outputVolt -= 0.425;
                                                                                              if (outputVolt > 46) {
                                                                                                outputVolt -= 0.425;
                                                                                                if (outputVolt > 47) {
                                                                                                  outputVolt -= 0.425;
                                                                                                  if (outputVolt > 48) {
                                                                                                    outputVolt -= 0.425;
                                                                                                    if (outputVolt > 49) {
                                                                                                      outputVolt -= 0.425;
                                                                                                      if (outputVolt > 50) {
                                                                                                        outputVolt -= 0.425;
                                                                                                      }
                                                                                                    }
                                                                                                  }
                                                                                                }
                                                                                              }
                                                                                            }
                                                                                          }
                                                                                        }
                                                                                      }
                                                                                    }
                                                                                  }
                                                                                }
                                                                              }
                                                                            }
                                                                          }
                                                                        }
                                                                      }
                                                                    }
                                                                  }
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  Serial.print(inputanVolt, 2);
  Serial.print("=");
  Serial.println(fixArusin, 2);

  if (Serial.available() > 0) {
    String dataMasuk = Serial.readStringUntil('\n');
    String modeGUI = splittt(dataMasuk, '=', 0);
    String pwmGUI = splittt(dataMasuk, '=', 1);
    if (modeGUI == "Boost") {
      Serial.print("  MODE BOOST =");
      Serial.print(outputVolt, 2);
      Serial.print("=");
      Serial.println(fixArusout);
      digitalWrite(pwmDM, pwmGUI.toInt());
    } else if (modeGUI == "Buck") {
      Serial.print("  MODE BUCK  =");
      Serial.print(outputVolt, 2);
      Serial.print("=");
      Serial.println(fixArusout);
      digitalWrite(pwmDM, pwmGUI.toInt());
    } else if (modeGUI == "Normal") {
      Serial.print(" MODE NORMAL =");
      Serial.print(outputVolt, 2);
      Serial.print("=");
      Serial.println(fixArusout);
      digitalWrite(pwmDM, pwmGUI.toInt());
    }
  } else {
    Serial.print("");
  }
}

String splittt(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}