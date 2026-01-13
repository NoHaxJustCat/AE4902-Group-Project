/**
 * Integer-Only Random Forest Regressor
 * ======================================
 * 
 * Post-processed from emlearn inline export for true integer-only inference.
 * 
 * Model Configuration:
 *   - Trees: 4
 *   - Features: 4
 *   - Target scale: 10000 (Y_SCALE)
 * 
 * Feature Order (all int16):
 *   0: Temp_ewma_q
 *   1: base_capacity_q
 *   2: Voltage_ewma_q
 *   3: Current_ewma_q
 * 
 * Usage:
 *   int16_t features[4] = {temp_q, cap_q, volt_q, curr_q};
 *   int32_t ah_q = model_Nico_allparams_predict(features, 4);
 *   float ah = (float)ah_q / 10000.0f;
 * 
 * Integer-Only Guarantees:
 *   - Leaf values: int16 literals (NOT float)
 *   - Tree returns: int32_t (cast from int16)
 *   - Forest accumulation: int32_t sum (NO float arithmetic)
 *   - Final result: int32_t (quantized Ah * 10000)
 * 
 * Flash/RAM:
 *   - Method: inline (all data in flash/PROGMEM)
 *   - RAM usage: ~0 bytes (no model struct)
 *   - No float library required!
 */

#ifndef MODEL_NICO_ALLPARAMS_H
#define MODEL_NICO_ALLPARAMS_H

#include <stdint.h>

// Model configuration constants
#define RF_MODEL_N_TREES 4
#define RF_MODEL_N_FEATURES 4
#define RF_MODEL_Y_SCALE 10000

// Backward compatibility aliases
#define MODEL_NICO_ALLPARAMS_N_TREES RF_MODEL_N_TREES
#define MODEL_NICO_ALLPARAMS_N_FEATURES RF_MODEL_N_FEATURES
#define MODEL_NICO_ALLPARAMS_Y_SCALE RF_MODEL_Y_SCALE

// Function alias for compatibility
#define rf_model_predict model_Nico_allparams_predict




    // !!! This file is generated using emlearn !!!

    #include <stdint.h>
    

static inline int32_t model_Nico_allparams_tree_0(const int16 *features, int32_t features_length) {
          if (features[2] < 7260) {
              if (features[2] < 6859) {
                  if (features[0] < 214) {
                      if (features[2] < 6625) {
                          if (features[0] < -3998) {
                              if (features[3] < -5518) {
                                  if (features[0] < -6281) {
                                      if (features[2] < 6365) {
                                          return 13045;
                                      } else {
                                          return 15571;
                                      }
                                  } else {
                                      if (features[3] < -8044) {
                                          return 15098;
                                      } else {
                                          return 13093;
                                      }
                                  }
                              } else {
                                  if (features[3] < -4391) {
                                      if (features[3] < -4970) {
                                          return 12979;
                                      } else {
                                          return 12440;
                                      }
                                  } else {
                                      if (features[3] < -3906) {
                                          return 12097;
                                      } else {
                                          return 11693;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -7676) {
                                  if (features[2] < 6375) {
                                      if (features[2] < 6254) {
                                          return 12293;
                                      } else {
                                          return 13931;
                                      }
                                  } else {
                                      if (features[2] < 6426) {
                                          return 14539;
                                      } else {
                                          return 16268;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6561) {
                                      if (features[2] < 6249) {
                                          return 9215;
                                      } else {
                                          return 9828;
                                      }
                                  } else {
                                      if (features[0] < -3573) {
                                          return 9313;
                                      } else {
                                          return 11160;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < -4334) {
                              if (features[0] < -7580) {
                                  if (features[0] < -7810) {
                                      if (features[0] < -8109) {
                                          return 14185;
                                      } else {
                                          return 12987;
                                      }
                                  } else {
                                      if (features[2] < 6761) {
                                          return 14188;
                                      } else {
                                          return 18723;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5740) {
                                      if (features[0] < -6673) {
                                          return 19356;
                                      } else {
                                          return 17814;
                                      }
                                  } else {
                                      if (features[0] < -7164) {
                                          return 16158;
                                      } else {
                                          return 15131;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -3876) {
                                  if (features[3] < -5214) {
                                      if (features[2] < 6656) {
                                          return 19187;
                                      } else {
                                          return 15832;
                                      }
                                  } else {
                                      if (features[2] < 6777) {
                                          return 9376;
                                      } else {
                                          return 11889;
                                      }
                                  }
                              } else {
                                  if (features[3] < -7007) {
                                      if (features[2] < 6712) {
                                          return 17722;
                                      } else {
                                          return 19120;
                                      }
                                  } else {
                                      if (features[3] < -4348) {
                                          return 13914;
                                      } else {
                                          return 11358;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[0] < 13532) {
                          if (features[3] < -2720) {
                              if (features[2] < 6653) {
                                  if (features[2] < 6349) {
                                      if (features[2] < 6187) {
                                          return 3894;
                                      } else {
                                          return 4621;
                                      }
                                  } else {
                                      if (features[3] < -7478) {
                                          return 7630;
                                      } else {
                                          return 6154;
                                      }
                                  }
                              } else {
                                  if (features[3] < -4216) {
                                      if (features[0] < 6258) {
                                          return 10018;
                                      } else {
                                          return 6782;
                                      }
                                  } else {
                                      if (features[0] < 4250) {
                                          return 8669;
                                      } else {
                                          return 6454;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 6646) {
                                  if (features[0] < 1538) {
                                      if (features[0] < 1451) {
                                          return 2947;
                                      } else {
                                          return 3191;
                                      }
                                  } else {
                                      if (features[2] < 6541) {
                                          return 3324;
                                      } else {
                                          return 4520;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6820) {
                                      if (features[0] < 1275) {
                                          return 7417;
                                      } else {
                                          return 5420;
                                      }
                                  } else {
                                      if (features[0] < 6256) {
                                          return 6280;
                                      } else {
                                          return 6899;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[3] < -2419) {
                              if (features[2] < 6638) {
                                  if (features[3] < -6222) {
                                      if (features[2] < 6502) {
                                          return 2304;
                                      } else {
                                          return 3808;
                                      }
                                  } else {
                                      if (features[0] < 14018) {
                                          return 3189;
                                      } else {
                                          return 2291;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6746) {
                                      if (features[2] < 6711) {
                                          return 4407;
                                      } else {
                                          return 4752;
                                      }
                                  } else {
                                      if (features[3] < -6590) {
                                          return 6443;
                                      } else {
                                          return 5509;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -1856) {
                                  if (features[2] < 6591) {
                                      if (features[2] < 6503) {
                                          return 1603;
                                      } else {
                                          return 2876;
                                      }
                                  } else {
                                      if (features[2] < 6717) {
                                          return 3518;
                                      } else {
                                          return 5071;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6561) {
                                      if (features[2] < 6266) {
                                          return 1043;
                                      } else {
                                          return 1919;
                                      }
                                  } else {
                                      if (features[2] < 6721) {
                                          return 3286;
                                      } else {
                                          return 4885;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[0] < 154) {
                      if (features[3] < -3997) {
                          if (features[0] < -3582) {
                              if (features[0] < -7593) {
                                  if (features[3] < -4802) {
                                      if (features[2] < 7138) {
                                          return 22739;
                                      } else {
                                          return 25368;
                                      }
                                  } else {
                                      if (features[0] < -7945) {
                                          return 23194;
                                      } else {
                                          return 20286;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7048) {
                                      if (features[3] < -5251) {
                                          return 21411;
                                      } else {
                                          return 19596;
                                      }
                                  } else {
                                      if (features[0] < -7496) {
                                          return 23491;
                                      } else {
                                          return 22749;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7069) {
                                  if (features[0] < -3045) {
                                      if (features[2] < 6910) {
                                          return 19881;
                                      } else {
                                          return 17847;
                                      }
                                  } else {
                                      if (features[3] < -7813) {
                                          return 18335;
                                      } else {
                                          return 16544;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7164) {
                                      if (features[3] < -5736) {
                                          return 20175;
                                      } else {
                                          return 19106;
                                      }
                                  } else {
                                      if (features[3] < -5331) {
                                          return 21160;
                                      } else {
                                          return 19640;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < -5963) {
                              if (features[0] < -7858) {
                                  if (features[0] < -8410) {
                                      if (features[2] < 6971) {
                                          return 17262;
                                      } else {
                                          return 18687;
                                      }
                                  } else {
                                      if (features[0] < -7949) {
                                          return 18585;
                                      } else {
                                          return 19164;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7117) {
                                      if (features[2] < 6962) {
                                          return 17951;
                                      } else {
                                          return 19680;
                                      }
                                  } else {
                                      if (features[2] < 7233) {
                                          return 21641;
                                      } else {
                                          return 24243;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7002) {
                                  if (features[3] < -2625) {
                                      if (features[2] < 6958) {
                                          return 13943;
                                      } else {
                                          return 14998;
                                      }
                                  } else {
                                      if (features[0] < -4355) {
                                          return 13803;
                                      } else {
                                          return 14188;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7138) {
                                      if (features[0] < -3249) {
                                          return 16065;
                                      } else {
                                          return 16372;
                                      }
                                  } else {
                                      if (features[3] < -2910) {
                                          return 18200;
                                      } else {
                                          return 17020;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[0] < 5433) {
                          if (features[0] < 2569) {
                              if (features[0] < 1526) {
                                  if (features[0] < 1092) {
                                      if (features[0] < 988) {
                                          return 14396;
                                      } else {
                                          return 15560;
                                      }
                                  } else {
                                      if (features[3] < -3096) {
                                          return 14200;
                                      } else {
                                          return 15465;
                                      }
                                  }
                              } else {
                                  if (features[0] < 1945) {
                                      if (features[0] < 1615) {
                                          return 15200;
                                      } else {
                                          return 16287;
                                      }
                                  } else {
                                      if (features[3] < -8281) {
                                          return 16619;
                                      } else {
                                          return 14647;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7041) {
                                  if (features[2] < 6933) {
                                      if (features[0] < 2801) {
                                          return 13559;
                                      } else {
                                          return 13802;
                                      }
                                  } else {
                                      if (features[0] < 2783) {
                                          return 14443;
                                      } else {
                                          return 14179;
                                      }
                                  }
                              } else {
                                  if (features[3] < -3660) {
                                      if (features[0] < 2805) {
                                          return 17684;
                                      } else {
                                          return 18009;
                                      }
                                  } else {
                                      if (features[0] < 5432) {
                                          return 14172;
                                      } else {
                                          return 14025;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 13266) {
                              if (features[3] < -2092) {
                                  if (features[2] < 7114) {
                                      if (features[2] < 6964) {
                                          return 8835;
                                      } else {
                                          return 11184;
                                      }
                                  } else {
                                      if (features[2] < 7168) {
                                          return 13044;
                                      } else {
                                          return 14472;
                                      }
                                  }
                              } else {
                                  if (features[0] < 5522) {
                                      if (features[2] < 7138) {
                                          return 10950;
                                      } else {
                                          return 12770;
                                      }
                                  } else {
                                      if (features[3] < -1537) {
                                          return 10297;
                                      } else {
                                          return 8993;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7074) {
                                  if (features[2] < 6963) {
                                      if (features[3] < -3971) {
                                          return 8068;
                                      } else {
                                          return 7105;
                                      }
                                  } else {
                                      if (features[3] < -5614) {
                                          return 10209;
                                      } else {
                                          return 8989;
                                      }
                                  }
                              } else {
                                  if (features[0] < 13753) {
                                      if (features[2] < 7177) {
                                          return 11659;
                                      } else {
                                          return 13471;
                                      }
                                  } else {
                                      if (features[0] < 13761) {
                                          return 11283;
                                      } else {
                                          return 11407;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          } else {
              if (features[3] < -917) {
                  if (features[0] < 1120) {
                      if (features[0] < -4550) {
                          if (features[3] < -1957) {
                              if (features[2] < 7398) {
                                  if (features[3] < -4251) {
                                      if (features[0] < -7758) {
                                          return 26607;
                                      } else {
                                          return 25298;
                                      }
                                  } else {
                                      if (features[3] < -2929) {
                                          return 24573;
                                      } else {
                                          return 23454;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7640) {
                                      if (features[3] < -6086) {
                                          return 27530;
                                      } else {
                                          return 26960;
                                      }
                                  } else {
                                      if (features[2] < 7810) {
                                          return 27984;
                                      } else {
                                          return 28513;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -1903) {
                                  if (features[3] < -1942) {
                                      if (features[2] < 7615) {
                                          return 23024;
                                      } else {
                                          return 28486;
                                      }
                                  } else {
                                      if (features[0] < -9194) {
                                          return 26726;
                                      } else {
                                          return 28505;
                                      }
                                  }
                              } else {
                                  if (features[3] < -1551) {
                                      if (features[2] < 8137) {
                                          return 28581;
                                      } else {
                                          return 28656;
                                      }
                                  } else {
                                      if (features[2] < 8205) {
                                          return 28743;
                                      } else {
                                          return 28789;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7509) {
                              if (features[3] < -3915) {
                                  if (features[2] < 7396) {
                                      if (features[2] < 7271) {
                                          return 22469;
                                      } else {
                                          return 21514;
                                      }
                                  } else {
                                      if (features[0] < -1024) {
                                          return 23961;
                                      } else {
                                          return 19982;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7438) {
                                      if (features[2] < 7370) {
                                          return 19953;
                                      } else {
                                          return 18952;
                                      }
                                  } else {
                                      if (features[2] < 7490) {
                                          return 21978;
                                      } else {
                                          return 20384;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7792) {
                                  if (features[2] < 7645) {
                                      if (features[0] < -1130) {
                                          return 24983;
                                      } else {
                                          return 22780;
                                      }
                                  } else {
                                      if (features[3] < -3120) {
                                          return 26321;
                                      } else {
                                          return 24672;
                                      }
                                  }
                              } else {
                                  if (features[0] < 915) {
                                      if (features[2] < 7981) {
                                          return 27514;
                                      } else {
                                          return 28428;
                                      }
                                  } else {
                                      if (features[2] < 7894) {
                                          return 26452;
                                      } else {
                                          return 27301;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[2] < 7713) {
                          if (features[3] < -3389) {
                              if (features[3] < -6198) {
                                  if (features[3] < -9236) {
                                      if (features[2] < 7539) {
                                          return 19910;
                                      } else {
                                          return 24176;
                                      }
                                  } else {
                                      if (features[2] < 7444) {
                                          return 19221;
                                      } else {
                                          return 21584;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5757) {
                                      if (features[0] < 4449) {
                                          return 21537;
                                      } else {
                                          return 17873;
                                      }
                                  } else {
                                      if (features[2] < 7486) {
                                          return 17302;
                                      } else {
                                          return 20942;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7448) {
                                  if (features[0] < 9841) {
                                      if (features[3] < -1916) {
                                          return 16473;
                                      } else {
                                          return 15560;
                                      }
                                  } else {
                                      if (features[2] < 7343) {
                                          return 14699;
                                      } else {
                                          return 16211;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7611) {
                                      if (features[0] < 3792) {
                                          return 20789;
                                      } else {
                                          return 18781;
                                      }
                                  } else {
                                      if (features[3] < -1352) {
                                          return 20693;
                                      } else {
                                          return 21090;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7925) {
                              if (features[0] < 3821) {
                                  if (features[3] < -4456) {
                                      if (features[2] < 7754) {
                                          return 25353;
                                      } else {
                                          return 26317;
                                      }
                                  } else {
                                      if (features[0] < 1279) {
                                          return 25017;
                                      } else {
                                          return 25490;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7793) {
                                      if (features[2] < 7750) {
                                          return 21993;
                                      } else {
                                          return 22695;
                                      }
                                  } else {
                                      if (features[2] < 7857) {
                                          return 23421;
                                      } else {
                                          return 24470;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 8105) {
                                  if (features[3] < -4582) {
                                      if (features[0] < 13077) {
                                          return 26988;
                                      } else {
                                          return 25027;
                                      }
                                  } else {
                                      if (features[2] < 8018) {
                                          return 25372;
                                      } else {
                                          return 26224;
                                      }
                                  }
                              } else {
                                  if (features[0] < 12971) {
                                      if (features[2] < 8194) {
                                          return 27734;
                                      } else {
                                          return 28465;
                                      }
                                  } else {
                                      if (features[0] < 13375) {
                                          return 27281;
                                      } else {
                                          return 26596;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[2] < 7965) {
                      if (features[2] < 7775) {
                          if (features[0] < 12847) {
                              if (features[0] < 12816) {
                                  if (features[0] < 12811) {
                                      if (features[3] < -911) {
                                          return 21656;
                                      } else {
                                          return 21658;
                                      }
                                  } else {
                                      return 21657;
                                  }
                              } else {
                                  if (features[0] < 12821) {
                                      if (features[3] < -911) {
                                          return 21686;
                                      } else {
                                          return 21685;
                                      }
                                  } else {
                                      return 21686;
                                  }
                              }
                          } else {
                              if (features[0] < 12887) {
                                  if (features[0] < 12878) {
                                      if (features[0] < 12873) {
                                          return 21742;
                                      } else {
                                          return 21743;
                                      }
                                  } else {
                                      if (features[3] < -894) {
                                          return 21743;
                                      } else {
                                          return 21744;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7773) {
                                      return 21741;
                                  } else {
                                      return 21742;
                                  }
                              }
                          }
                      } else {
                          if (features[3] < -865) {
                              if (features[3] < -879) {
                                  if (features[3] < -896) {
                                      if (features[3] < -911) {
                                          return 21697;
                                      } else {
                                          return 21685;
                                      }
                                  } else {
                                      if (features[3] < -891) {
                                          return 21676;
                                      } else {
                                          return 21670;
                                      }
                                  }
                              } else {
                                  if (features[0] < 12837) {
                                      if (features[0] < 12814) {
                                          return 21657;
                                      } else {
                                          return 21682;
                                      }
                                  } else {
                                      if (features[0] < 12858) {
                                          return 21730;
                                      } else {
                                          return 21732;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 12833) {
                                  return 21656;
                              } else {
                                  if (features[0] < 12864) {
                                      if (features[0] < 12861) {
                                          return 21733;
                                      } else {
                                          return 21736;
                                      }
                                  } else {
                                      if (features[3] < -855) {
                                          return 21742;
                                      } else {
                                          return 21741;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[3] < -448) {
                          if (features[3] < -655) {
                              if (features[3] < -817) {
                                  if (features[0] < 5372) {
                                      if (features[2] < 8212) {
                                          return 28802;
                                      } else {
                                          return 28818;
                                      }
                                  } else {
                                      if (features[2] < 8342) {
                                          return 28836;
                                      } else {
                                          return 28852;
                                      }
                                  }
                              } else {
                                  if (features[3] < -741) {
                                      if (features[0] < 5370) {
                                          return 28842;
                                      } else {
                                          return 28855;
                                      }
                                  } else {
                                      if (features[0] < 2844) {
                                          return 28867;
                                      } else {
                                          return 28854;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -584) {
                                  if (features[3] < -632) {
                                      if (features[0] < 5366) {
                                          return 28874;
                                      } else {
                                          return 28884;
                                      }
                                  } else {
                                      if (features[2] < 8305) {
                                          return 28882;
                                      } else {
                                          return 28890;
                                      }
                                  }
                              } else {
                                  if (features[3] < -491) {
                                      if (features[0] < 5365) {
                                          return 28897;
                                      } else {
                                          return 28904;
                                      }
                                  } else {
                                      if (features[2] < 8353) {
                                          return 28911;
                                      } else {
                                          return 28919;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < -4814) {
                              if (features[3] < -167) {
                                  if (features[2] < 8266) {
                                      if (features[0] < -10162) {
                                          return 28938;
                                      } else {
                                          return 28926;
                                      }
                                  } else {
                                      if (features[0] < -5049) {
                                          return 28960;
                                      } else {
                                          return 28949;
                                      }
                                  }
                              } else {
                                  if (features[3] < -91) {
                                      if (features[3] < -124) {
                                          return 28978;
                                      } else {
                                          return 28983;
                                      }
                                  } else {
                                      if (features[3] < -61) {
                                          return 28994;
                                      } else {
                                          return 28998;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -164) {
                                  if (features[2] < 8330) {
                                      if (features[3] < -344) {
                                          return 28929;
                                      } else {
                                          return 28950;
                                      }
                                  } else {
                                      if (features[0] < 437) {
                                          return 28962;
                                      } else {
                                          return 28950;
                                      }
                                  }
                              } else {
                                  if (features[0] < 12818) {
                                      if (features[3] < -85) {
                                          return 28979;
                                      } else {
                                          return 28998;
                                      }
                                  } else {
                                      if (features[0] < 12819) {
                                          return 28975;
                                      } else {
                                          return 28978;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
        }
        

static inline int32_t model_Nico_allparams_tree_1(const int16 *features, int32_t features_length) {
          if (features[2] < 7258) {
              if (features[2] < 6859) {
                  if (features[0] < 214) {
                      if (features[2] < 6625) {
                          if (features[0] < -3992) {
                              if (features[2] < 6380) {
                                  if (features[0] < -7511) {
                                      if (features[2] < 6319) {
                                          return 11678;
                                      } else {
                                          return 11865;
                                      }
                                  } else {
                                      if (features[3] < -6903) {
                                          return 13223;
                                      } else {
                                          return 12102;
                                      }
                                  }
                              } else {
                                  if (features[0] < -7844) {
                                      if (features[0] < -8166) {
                                          return 12229;
                                      } else {
                                          return 12959;
                                      }
                                  } else {
                                      if (features[3] < -5269) {
                                          return 15311;
                                      } else {
                                          return 12399;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -7677) {
                                  if (features[0] < -2053) {
                                      if (features[2] < 6397) {
                                          return 12755;
                                      } else {
                                          return 16221;
                                      }
                                  } else {
                                      if (features[0] < -1478) {
                                          return 13056;
                                      } else {
                                          return 11825;
                                      }
                                  }
                              } else {
                                  if (features[0] < -2462) {
                                      if (features[3] < -4708) {
                                          return 11511;
                                      } else {
                                          return 9576;
                                      }
                                  } else {
                                      if (features[2] < 6513) {
                                          return 9496;
                                      } else {
                                          return 8745;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < -4335) {
                              if (features[3] < -3756) {
                                  if (features[2] < 6695) {
                                      if (features[3] < -6761) {
                                          return 18708;
                                      } else {
                                          return 15592;
                                      }
                                  } else {
                                      if (features[3] < -5887) {
                                          return 19066;
                                      } else {
                                          return 16950;
                                      }
                                  }
                              } else {
                                  if (features[0] < -6788) {
                                      if (features[3] < -3115) {
                                          return 14569;
                                      } else {
                                          return 12672;
                                      }
                                  } else {
                                      if (features[3] < -3319) {
                                          return 14323;
                                      } else {
                                          return 11600;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -3876) {
                                  if (features[3] < -5215) {
                                      if (features[2] < 6657) {
                                          return 19188;
                                      } else {
                                          return 15833;
                                      }
                                  } else {
                                      if (features[3] < -1940) {
                                          return 11752;
                                      } else {
                                          return 8700;
                                      }
                                  }
                              } else {
                                  if (features[3] < -7007) {
                                      if (features[3] < -11199) {
                                          return 21158;
                                      } else {
                                          return 18132;
                                      }
                                  } else {
                                      if (features[3] < -4341) {
                                          return 13916;
                                      } else {
                                          return 11362;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[3] < -3438) {
                          if (features[0] < 3088) {
                              if (features[2] < 6643) {
                                  if (features[0] < 2087) {
                                      if (features[2] < 6043) {
                                          return 3552;
                                      } else {
                                          return 7141;
                                      }
                                  } else {
                                      if (features[3] < -8544) {
                                          return 9629;
                                      } else {
                                          return 6078;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6767) {
                                      if (features[3] < -6452) {
                                          return 10131;
                                      } else {
                                          return 8779;
                                      }
                                  } else {
                                      if (features[3] < -5403) {
                                          return 11422;
                                      } else {
                                          return 10361;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 6652) {
                                  if (features[0] < 11328) {
                                      if (features[3] < -7477) {
                                          return 7080;
                                      } else {
                                          return 4943;
                                      }
                                  } else {
                                      if (features[0] < 13839) {
                                          return 3638;
                                      } else {
                                          return 2704;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6821) {
                                      if (features[0] < 11113) {
                                          return 7263;
                                      } else {
                                          return 5419;
                                      }
                                  } else {
                                      if (features[3] < -4853) {
                                          return 7807;
                                      } else {
                                          return 6990;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 6663) {
                              if (features[0] < 13435) {
                                  if (features[3] < -1698) {
                                      if (features[2] < 6457) {
                                          return 3446;
                                      } else {
                                          return 4815;
                                      }
                                  } else {
                                      if (features[2] < 6583) {
                                          return 3138;
                                      } else {
                                          return 5250;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6509) {
                                      if (features[3] < -2339) {
                                          return 2027;
                                      } else {
                                          return 1494;
                                      }
                                  } else {
                                      if (features[2] < 6602) {
                                          return 2957;
                                      } else {
                                          return 3380;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 3754) {
                                  if (features[2] < 6776) {
                                      if (features[0] < 1013) {
                                          return 7385;
                                      } else {
                                          return 8060;
                                      }
                                  } else {
                                      if (features[0] < 1296) {
                                          return 10415;
                                      } else {
                                          return 9558;
                                      }
                                  }
                              } else {
                                  if (features[3] < -2664) {
                                      if (features[2] < 6816) {
                                          return 5368;
                                      } else {
                                          return 6771;
                                      }
                                  } else {
                                      if (features[2] < 6807) {
                                          return 5174;
                                      } else {
                                          return 6423;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[0] < 154) {
                      if (features[3] < -3994) {
                          if (features[2] < 7066) {
                              if (features[0] < -3467) {
                                  if (features[2] < 6938) {
                                      if (features[0] < -7430) {
                                          return 19140;
                                      } else {
                                          return 20385;
                                      }
                                  } else {
                                      if (features[2] < 7048) {
                                          return 21201;
                                      } else {
                                          return 22495;
                                      }
                                  }
                              } else {
                                  if (features[0] < -3030) {
                                      if (features[0] < -3432) {
                                          return 17070;
                                      } else {
                                          return 18874;
                                      }
                                  } else {
                                      if (features[0] < -1724) {
                                          return 16537;
                                      } else {
                                          return 17576;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -3746) {
                                  if (features[2] < 7179) {
                                      if (features[0] < -7517) {
                                          return 23457;
                                      } else {
                                          return 22431;
                                      }
                                  } else {
                                      if (features[3] < -4994) {
                                          return 25381;
                                      } else {
                                          return 23498;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5736) {
                                      if (features[2] < 7166) {
                                          return 20153;
                                      } else {
                                          return 21158;
                                      }
                                  } else {
                                      if (features[2] < 7224) {
                                          return 19101;
                                      } else {
                                          return 20416;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7007) {
                              if (features[2] < 6951) {
                                  if (features[2] < 6894) {
                                      if (features[3] < -3158) {
                                          return 15026;
                                      } else {
                                          return 16551;
                                      }
                                  } else {
                                      if (features[3] < -3448) {
                                          return 18101;
                                      } else {
                                          return 17098;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6996) {
                                      if (features[2] < 6965) {
                                          return 14183;
                                      } else {
                                          return 14632;
                                      }
                                  } else {
                                      if (features[0] < -5825) {
                                          return 19383;
                                      } else {
                                          return 15581;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7172) {
                                  if (features[2] < 7127) {
                                      if (features[0] < -5242) {
                                          return 19194;
                                      } else {
                                          return 16157;
                                      }
                                  } else {
                                      if (features[3] < -3273) {
                                          return 18737;
                                      } else {
                                          return 17015;
                                      }
                                  }
                              } else {
                                  if (features[3] < -3572) {
                                      if (features[0] < -5198) {
                                          return 22018;
                                      } else {
                                          return 18514;
                                      }
                                  } else {
                                      if (features[0] < -5645) {
                                          return 21435;
                                      } else {
                                          return 18498;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[2] < 7119) {
                          if (features[0] < 4148) {
                              if (features[3] < -7256) {
                                  if (features[3] < -9043) {
                                      if (features[0] < 2320) {
                                          return 15295;
                                      } else {
                                          return 14622;
                                      }
                                  } else {
                                      if (features[0] < 1994) {
                                          return 15923;
                                      } else {
                                          return 14029;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6966) {
                                      if (features[2] < 6889) {
                                          return 11669;
                                      } else {
                                          return 12684;
                                      }
                                  } else {
                                      if (features[2] < 7031) {
                                          return 13759;
                                      } else {
                                          return 14832;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 12984) {
                                  if (features[3] < -4939) {
                                      if (features[2] < 6939) {
                                          return 10088;
                                      } else {
                                          return 12504;
                                      }
                                  } else {
                                      if (features[2] < 6981) {
                                          return 8242;
                                      } else {
                                          return 10618;
                                      }
                                  }
                              } else {
                                  if (features[0] < 13309) {
                                      if (features[2] < 6985) {
                                          return 7665;
                                      } else {
                                          return 10530;
                                      }
                                  } else {
                                      if (features[2] < 7004) {
                                          return 8061;
                                      } else {
                                          return 10254;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 4169) {
                              if (features[2] < 7195) {
                                  if (features[3] < -5253) {
                                      if (features[0] < 2437) {
                                          return 16484;
                                      } else {
                                          return 17463;
                                      }
                                  } else {
                                      if (features[3] < -3287) {
                                          return 15907;
                                      } else {
                                          return 15105;
                                      }
                                  }
                              } else {
                                  if (features[3] < -6508) {
                                      if (features[3] < -8231) {
                                          return 18541;
                                      } else {
                                          return 17991;
                                      }
                                  } else {
                                      if (features[2] < 7226) {
                                          return 16854;
                                      } else {
                                          return 17225;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7190) {
                                  if (features[0] < 10608) {
                                      if (features[0] < 5764) {
                                          return 12539;
                                      } else {
                                          return 13618;
                                      }
                                  } else {
                                      if (features[3] < -4697) {
                                          return 12867;
                                      } else {
                                          return 12016;
                                      }
                                  }
                              } else {
                                  if (features[0] < 10513) {
                                      if (features[0] < 5671) {
                                          return 13480;
                                      } else {
                                          return 15126;
                                      }
                                  } else {
                                      if (features[2] < 7237) {
                                          return 13348;
                                      } else {
                                          return 14015;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          } else {
              if (features[2] < 7728) {
                  if (features[0] < -2981) {
                      if (features[3] < -3707) {
                          if (features[2] < 7480) {
                              if (features[0] < -4512) {
                                  if (features[2] < 7378) {
                                      if (features[0] < -7877) {
                                          return 26322;
                                      } else {
                                          return 25261;
                                      }
                                  } else {
                                      if (features[0] < -7933) {
                                          return 26974;
                                      } else {
                                          return 25534;
                                      }
                                  }
                              } else {
                                  if (features[0] < -4352) {
                                      if (features[2] < 7422) {
                                          return 20924;
                                      } else {
                                          return 23331;
                                      }
                                  } else {
                                      if (features[3] < -7390) {
                                          return 25002;
                                      } else {
                                          return 22994;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -3663) {
                                  if (features[0] < -8256) {
                                      if (features[0] < -9014) {
                                          return 28130;
                                      } else {
                                          return 27674;
                                      }
                                  } else {
                                      if (features[3] < -3868) {
                                          return 27001;
                                      } else {
                                          return 26200;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7573) {
                                      if (features[0] < -3636) {
                                          return 23978;
                                      } else {
                                          return 25397;
                                      }
                                  } else {
                                      if (features[0] < -3465) {
                                          return 26600;
                                      } else {
                                          return 25818;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7498) {
                              if (features[2] < 7328) {
                                  if (features[2] < 7290) {
                                      if (features[3] < -2748) {
                                          return 22884;
                                      } else {
                                          return 18832;
                                      }
                                  } else {
                                      if (features[3] < -2531) {
                                          return 21542;
                                      } else {
                                          return 19503;
                                      }
                                  }
                              } else {
                                  if (features[3] < -2782) {
                                      if (features[2] < 7339) {
                                          return 22634;
                                      } else {
                                          return 23588;
                                      }
                                  } else {
                                      if (features[2] < 7332) {
                                          return 21084;
                                      } else {
                                          return 22200;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -2931) {
                                  if (features[2] < 7665) {
                                      if (features[2] < 7541) {
                                          return 26144;
                                      } else {
                                          return 25164;
                                      }
                                  } else {
                                      if (features[3] < -3433) {
                                          return 26908;
                                      } else {
                                          return 27655;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7597) {
                                      if (features[3] < -2527) {
                                          return 24085;
                                      } else {
                                          return 23638;
                                      }
                                  } else {
                                      if (features[3] < -2286) {
                                          return 24957;
                                      } else {
                                          return 24257;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[0] < 4269) {
                          if (features[3] < -3462) {
                              if (features[2] < 7480) {
                                  if (features[0] < -611) {
                                      if (features[0] < -2617) {
                                          return 21626;
                                      } else {
                                          return 20970;
                                      }
                                  } else {
                                      if (features[0] < 1426) {
                                          return 18761;
                                      } else {
                                          return 19903;
                                      }
                                  }
                              } else {
                                  if (features[3] < -7695) {
                                      if (features[0] < 2890) {
                                          return 24795;
                                      } else {
                                          return 23122;
                                      }
                                  } else {
                                      if (features[3] < -3868) {
                                          return 22952;
                                      } else {
                                          return 22123;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -2754) {
                                  if (features[2] < 7462) {
                                      if (features[0] < 1135) {
                                          return 19086;
                                      } else {
                                          return 17486;
                                      }
                                  } else {
                                      if (features[0] < 1203) {
                                          return 21545;
                                      } else {
                                          return 20988;
                                      }
                                  }
                              } else {
                                  if (features[0] < 927) {
                                      if (features[3] < -1830) {
                                          return 19006;
                                      } else {
                                          return 19485;
                                      }
                                  } else {
                                      if (features[0] < 1064) {
                                          return 19919;
                                      } else {
                                          return 20360;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 7875) {
                              if (features[2] < 7497) {
                                  if (features[3] < -3374) {
                                      if (features[0] < 7159) {
                                          return 17520;
                                      } else {
                                          return 19022;
                                      }
                                  } else {
                                      if (features[3] < -1919) {
                                          return 16812;
                                      } else {
                                          return 16223;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7627) {
                                      if (features[2] < 7532) {
                                          return 19037;
                                      } else {
                                          return 20095;
                                      }
                                  } else {
                                      if (features[3] < -4278) {
                                          return 22469;
                                      } else {
                                          return 21373;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7456) {
                                  if (features[3] < -4999) {
                                      if (features[2] < 7357) {
                                          return 16158;
                                      } else {
                                          return 16931;
                                      }
                                  } else {
                                      if (features[2] < 7359) {
                                          return 14894;
                                      } else {
                                          return 16535;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7608) {
                                      if (features[2] < 7519) {
                                          return 18034;
                                      } else {
                                          return 19072;
                                      }
                                  } else {
                                      if (features[2] < 7667) {
                                          return 20300;
                                      } else {
                                          return 21245;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[2] < 7941) {
                      if (features[2] < 7849) {
                          if (features[2] < 7751) {
                              if (features[2] < 7749) {
                                  if (features[0] < 3791) {
                                      if (features[0] < -1474) {
                                          return 27282;
                                      } else {
                                          return 24928;
                                      }
                                  } else {
                                      if (features[0] < 13163) {
                                          return 22288;
                                      } else {
                                          return 21673;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7750) {
                                      if (features[0] < 3737) {
                                          return 25114;
                                      } else {
                                          return 22279;
                                      }
                                  } else {
                                      if (features[0] < 3734) {
                                          return 25052;
                                      } else {
                                          return 22347;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 3731) {
                                  if (features[0] < -1487) {
                                      if (features[0] < -7337) {
                                          return 28287;
                                      } else {
                                          return 27174;
                                      }
                                  } else {
                                      if (features[2] < 7771) {
                                          return 24592;
                                      } else {
                                          return 25967;
                                      }
                                  }
                              } else {
                                  if (features[3] < -1899) {
                                      if (features[3] < -5273) {
                                          return 23960;
                                      } else {
                                          return 23235;
                                      }
                                  } else {
                                      if (features[2] < 7795) {
                                          return 22106;
                                      } else {
                                          return 23069;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[3] < -2913) {
                              if (features[0] < 3832) {
                                  if (features[3] < -8263) {
                                      if (features[3] < -10054) {
                                          return 28701;
                                      } else {
                                          return 28393;
                                      }
                                  } else {
                                      if (features[3] < -6135) {
                                          return 27625;
                                      } else {
                                          return 27269;
                                      }
                                  }
                              } else {
                                  if (features[0] < 10095) {
                                      if (features[0] < 6472) {
                                          return 25084;
                                      } else {
                                          return 25564;
                                      }
                                  } else {
                                      if (features[0] < 13130) {
                                          return 24243;
                                      } else {
                                          return 23905;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 3283) {
                                  if (features[3] < -2233) {
                                      if (features[3] < -2665) {
                                          return 27615;
                                      } else {
                                          return 27821;
                                      }
                                  } else {
                                      if (features[0] < -9431) {
                                          return 28465;
                                      } else {
                                          return 28399;
                                      }
                                  }
                              } else {
                                  if (features[0] < 12797) {
                                      if (features[3] < -1582) {
                                          return 24705;
                                      } else {
                                          return 24307;
                                      }
                                  } else {
                                      if (features[0] < 13168) {
                                          return 23582;
                                      } else {
                                          return 23877;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[0] < 5454) {
                          if (features[2] < 8067) {
                              if (features[0] < 573) {
                                  if (features[3] < -9815) {
                                      if (features[3] < -10092) {
                                          return 28837;
                                      } else {
                                          return 28678;
                                      }
                                  } else {
                                      if (features[0] < -9300) {
                                          return 28608;
                                      } else {
                                          return 28311;
                                      }
                                  }
                              } else {
                                  if (features[0] < 905) {
                                      if (features[0] < 637) {
                                          return 27997;
                                      } else {
                                          return 27877;
                                      }
                                  } else {
                                      if (features[3] < -3446) {
                                          return 27547;
                                      } else {
                                          return 26925;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -1239) {
                                  if (features[0] < 342) {
                                      if (features[0] < -10020) {
                                          return 28918;
                                      } else {
                                          return 28676;
                                      }
                                  } else {
                                      if (features[2] < 8235) {
                                          return 28438;
                                      } else {
                                          return 28717;
                                      }
                                  }
                              } else {
                                  if (features[3] < -532) {
                                      if (features[2] < 8235) {
                                          return 28800;
                                      } else {
                                          return 28840;
                                      }
                                  } else {
                                      if (features[0] < 5166) {
                                          return 28975;
                                      } else {
                                          return 28954;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[3] < -5461) {
                              if (features[2] < 8112) {
                                  if (features[2] < 8022) {
                                      if (features[0] < 6277) {
                                          return 26925;
                                      } else {
                                          return 26561;
                                      }
                                  } else {
                                      if (features[0] < 5715) {
                                          return 27607;
                                      } else {
                                          return 27217;
                                      }
                                  }
                              } else {
                                  if (features[3] < -9070) {
                                      if (features[3] < -9613) {
                                          return 28842;
                                      } else {
                                          return 28577;
                                      }
                                  } else {
                                      if (features[3] < -6863) {
                                          return 28300;
                                      } else {
                                          return 28105;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 8105) {
                                  if (features[3] < -3056) {
                                      if (features[0] < 11942) {
                                          return 26604;
                                      } else {
                                          return 25728;
                                      }
                                  } else {
                                      if (features[2] < 8021) {
                                          return 25345;
                                      } else {
                                          return 26158;
                                      }
                                  }
                              } else {
                                  if (features[2] < 8201) {
                                      if (features[2] < 8160) {
                                          return 27268;
                                      } else {
                                          return 27749;
                                      }
                                  } else {
                                      if (features[3] < -2038) {
                                          return 28217;
                                      } else {
                                          return 28786;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
        }
        

static inline int32_t model_Nico_allparams_tree_2(const int16 *features, int32_t features_length) {
          if (features[2] < 7260) {
              if (features[3] < -4157) {
                  if (features[2] < 6869) {
                      if (features[0] < 1391) {
                          if (features[0] < -2752) {
                              if (features[0] < -7129) {
                                  if (features[3] < -5148) {
                                      if (features[2] < 6680) {
                                          return 16086;
                                      } else {
                                          return 19252;
                                      }
                                  } else {
                                      if (features[3] < -4536) {
                                          return 16038;
                                      } else {
                                          return 14544;
                                      }
                                  }
                              } else {
                                  if (features[3] < -8486) {
                                      if (features[2] < 6374) {
                                          return 13323;
                                      } else {
                                          return 18217;
                                      }
                                  } else {
                                      if (features[2] < 6615) {
                                          return 13230;
                                      } else {
                                          return 15532;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -8720) {
                                  if (features[0] < -837) {
                                      if (features[2] < 6348) {
                                          return 12546;
                                      } else {
                                          return 15845;
                                      }
                                  } else {
                                      if (features[0] < -404) {
                                          return 17237;
                                      } else {
                                          return 16745;
                                      }
                                  }
                              } else {
                                  if (features[0] < -2232) {
                                      if (features[2] < 6550) {
                                          return 10198;
                                      } else {
                                          return 12721;
                                      }
                                  } else {
                                      if (features[0] < 1157) {
                                          return 9485;
                                      } else {
                                          return 10668;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 6651) {
                              if (features[3] < -7481) {
                                  if (features[2] < 6390) {
                                      if (features[2] < 6349) {
                                          return 5867;
                                      } else {
                                          return 6676;
                                      }
                                  } else {
                                      if (features[3] < -9958) {
                                          return 8505;
                                      } else {
                                          return 7204;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6377) {
                                      if (features[0] < 10857) {
                                          return 4390;
                                      } else {
                                          return 2054;
                                      }
                                  } else {
                                      if (features[0] < 11304) {
                                          return 6394;
                                      } else {
                                          return 3419;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 6809) {
                                  if (features[0] < 6236) {
                                      if (features[0] < 4714) {
                                          return 9451;
                                      } else {
                                          return 8048;
                                      }
                                  } else {
                                      if (features[3] < -6730) {
                                          return 7836;
                                      } else {
                                          return 5754;
                                      }
                                  }
                              } else {
                                  if (features[0] < 4427) {
                                      if (features[0] < 1859) {
                                          return 10941;
                                      } else {
                                          return 11631;
                                      }
                                  } else {
                                      if (features[0] < 10810) {
                                          return 8650;
                                      } else {
                                          return 6747;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[0] < 195) {
                          if (features[2] < 7065) {
                              if (features[3] < -5360) {
                                  if (features[2] < 6950) {
                                      if (features[3] < -6694) {
                                          return 19509;
                                      } else {
                                          return 18426;
                                      }
                                  } else {
                                      if (features[0] < -3611) {
                                          return 22245;
                                      } else {
                                          return 18250;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6957) {
                                      if (features[2] < 6933) {
                                          return 17894;
                                      } else {
                                          return 16231;
                                      }
                                  } else {
                                      if (features[0] < -4756) {
                                          return 20099;
                                      } else {
                                          return 16706;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -3740) {
                                  if (features[0] < -7593) {
                                      if (features[2] < 7178) {
                                          return 23700;
                                      } else {
                                          return 25431;
                                      }
                                  } else {
                                      if (features[2] < 7199) {
                                          return 22651;
                                      } else {
                                          return 24727;
                                      }
                                  }
                              } else {
                                  if (features[0] < -2900) {
                                      if (features[2] < 7160) {
                                          return 19516;
                                      } else {
                                          return 20848;
                                      }
                                  } else {
                                      if (features[3] < -7443) {
                                          return 20114;
                                      } else {
                                          return 20881;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 13232) {
                              if (features[2] < 7120) {
                                  if (features[2] < 6925) {
                                      if (features[0] < 4312) {
                                          return 12448;
                                      } else {
                                          return 9589;
                                      }
                                  } else {
                                      if (features[0] < 4294) {
                                          return 14116;
                                      } else {
                                          return 11923;
                                      }
                                  }
                              } else {
                                  if (features[3] < -6303) {
                                      if (features[2] < 7201) {
                                          return 16402;
                                      } else {
                                          return 17606;
                                      }
                                  } else {
                                      if (features[0] < 5843) {
                                          return 16527;
                                      } else {
                                          return 14175;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -4649) {
                                  if (features[2] < 7000) {
                                      if (features[2] < 6951) {
                                          return 8093;
                                      } else {
                                          return 9405;
                                      }
                                  } else {
                                      if (features[2] < 7097) {
                                          return 10535;
                                      } else {
                                          return 12368;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7056) {
                                      if (features[0] < 13244) {
                                          return 7133;
                                      } else {
                                          return 8454;
                                      }
                                  } else {
                                      if (features[0] < 13467) {
                                          return 12484;
                                      } else {
                                          return 11980;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[2] < 6895) {
                      if (features[2] < 6419) {
                          if (features[3] < -3028) {
                              if (features[0] < -174) {
                                  if (features[0] < -3959) {
                                      if (features[2] < 6399) {
                                          return 11600;
                                      } else {
                                          return 11663;
                                      }
                                  } else {
                                      return 8699;
                                  }
                              } else {
                                  if (features[3] < -3904) {
                                      if (features[0] < 10783) {
                                          return 4069;
                                      } else {
                                          return 2096;
                                      }
                                  } else {
                                      if (features[2] < 6271) {
                                          return 3663;
                                      } else {
                                          return 2304;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 10485) {
                                  if (features[2] < 6395) {
                                      if (features[3] < -1954) {
                                          return 3409;
                                      } else {
                                          return 3003;
                                      }
                                  } else {
                                      if (features[0] < -377) {
                                          return 11600;
                                      } else {
                                          return 3594;
                                      }
                                  }
                              } else {
                                  if (features[0] < 13929) {
                                      if (features[2] < 6171) {
                                          return 1035;
                                      } else {
                                          return 1298;
                                      }
                                  } else {
                                      if (features[0] < 14112) {
                                          return 1640;
                                      } else {
                                          return 1923;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 1610) {
                              if (features[0] < -3757) {
                                  if (features[2] < 6843) {
                                      if (features[0] < -6572) {
                                          return 13152;
                                      } else {
                                          return 11294;
                                      }
                                  } else {
                                      if (features[0] < -5076) {
                                          return 17420;
                                      } else {
                                          return 13315;
                                      }
                                  }
                              } else {
                                  if (features[3] < -3175) {
                                      if (features[0] < -2480) {
                                          return 11302;
                                      } else {
                                          return 9026;
                                      }
                                  } else {
                                      if (features[2] < 6641) {
                                          return 8839;
                                      } else {
                                          return 7852;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 6672) {
                                  if (features[2] < 6496) {
                                      if (features[0] < 4566) {
                                          return 5803;
                                      } else {
                                          return 2548;
                                      }
                                  } else {
                                      if (features[0] < 5301) {
                                          return 5857;
                                      } else {
                                          return 3525;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6811) {
                                      if (features[0] < 4288) {
                                          return 8316;
                                      } else {
                                          return 5315;
                                      }
                                  } else {
                                      if (features[2] < 6839) {
                                          return 6363;
                                      } else {
                                          return 7158;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[3] < -2036) {
                          if (features[0] < 2136) {
                              if (features[0] < -4488) {
                                  if (features[0] < -7863) {
                                      if (features[2] < 6955) {
                                          return 17400;
                                      } else {
                                          return 18982;
                                      }
                                  } else {
                                      if (features[0] < -7758) {
                                          return 20035;
                                      } else {
                                          return 20475;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7126) {
                                      if (features[2] < 6965) {
                                          return 12746;
                                      } else {
                                          return 14628;
                                      }
                                  } else {
                                      if (features[2] < 7175) {
                                          return 16959;
                                      } else {
                                          return 16067;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 13753) {
                                  if (features[2] < 7112) {
                                      if (features[2] < 6993) {
                                          return 8275;
                                      } else {
                                          return 10737;
                                      }
                                  } else {
                                      if (features[2] < 7174) {
                                          return 12483;
                                      } else {
                                          return 13967;
                                      }
                                  }
                              } else {
                                  if (features[0] < 13841) {
                                      if (features[0] < 13788) {
                                          return 9911;
                                      } else {
                                          return 9262;
                                      }
                                  } else {
                                      if (features[2] < 6947) {
                                          return 7375;
                                      } else {
                                          return 8845;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[3] < -1732) {
                              if (features[2] < 7039) {
                                  if (features[0] < 662) {
                                      if (features[3] < -2020) {
                                          return 14788;
                                      } else {
                                          return 13850;
                                      }
                                  } else {
                                      if (features[0] < 9832) {
                                          return 9197;
                                      } else {
                                          return 7440;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7135) {
                                      if (features[3] < -1849) {
                                          return 11293;
                                      } else {
                                          return 10829;
                                      }
                                  } else {
                                      if (features[2] < 7148) {
                                          return 12361;
                                      } else {
                                          return 13606;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7097) {
                                  if (features[0] < 12989) {
                                      if (features[2] < 6987) {
                                          return 7494;
                                      } else {
                                          return 9640;
                                      }
                                  } else {
                                      if (features[3] < -1579) {
                                          return 7496;
                                      } else {
                                          return 6892;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7148) {
                                      if (features[2] < 7115) {
                                          return 10831;
                                      } else {
                                          return 11623;
                                      }
                                  } else {
                                      if (features[0] < 5436) {
                                          return 14217;
                                      } else {
                                          return 12871;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          } else {
              if (features[2] < 7728) {
                  if (features[3] < -3260) {
                      if (features[3] < -6197) {
                          if (features[2] < 7559) {
                              if (features[2] < 7381) {
                                  if (features[0] < -3107) {
                                      if (features[0] < -6497) {
                                          return 26999;
                                      } else {
                                          return 24698;
                                      }
                                  } else {
                                      if (features[0] < 4624) {
                                          return 19903;
                                      } else {
                                          return 17495;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7513) {
                                      if (features[3] < -8812) {
                                          return 19954;
                                      } else {
                                          return 21532;
                                      }
                                  } else {
                                      if (features[0] < -2294) {
                                          return 27676;
                                      } else {
                                          return 21378;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -936) {
                                  if (features[3] < -8358) {
                                      if (features[3] < -9447) {
                                          return 28300;
                                      } else {
                                          return 28123;
                                      }
                                  } else {
                                      if (features[3] < -6709) {
                                          return 27365;
                                      } else {
                                          return 27734;
                                      }
                                  }
                              } else {
                                  if (features[0] < 4817) {
                                      if (features[2] < 7623) {
                                          return 24132;
                                      } else {
                                          return 25494;
                                      }
                                  } else {
                                      if (features[3] < -8939) {
                                          return 23018;
                                      } else {
                                          return 21499;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7505) {
                              if (features[2] < 7420) {
                                  if (features[0] < -613) {
                                      if (features[0] < -4831) {
                                          return 25311;
                                      } else {
                                          return 21811;
                                      }
                                  } else {
                                      if (features[2] < 7369) {
                                          return 16399;
                                      } else {
                                          return 17764;
                                      }
                                  }
                              } else {
                                  if (features[0] < -1027) {
                                      if (features[0] < -5425) {
                                          return 26991;
                                      } else {
                                          return 23793;
                                      }
                                  } else {
                                      if (features[2] < 7486) {
                                          return 18721;
                                      } else {
                                          return 19445;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 1163) {
                                  if (features[3] < -5746) {
                                      if (features[0] < -3602) {
                                          return 27517;
                                      } else {
                                          return 25724;
                                      }
                                  } else {
                                      if (features[0] < -1171) {
                                          return 26120;
                                      } else {
                                          return 23673;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7627) {
                                      if (features[0] < 4255) {
                                          return 22152;
                                      } else {
                                          return 19790;
                                      }
                                  } else {
                                      if (features[0] < 3853) {
                                          return 24089;
                                      } else {
                                          return 21272;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[3] < -1950) {
                          if (features[2] < 7458) {
                              if (features[2] < 7313) {
                                  if (features[3] < -3185) {
                                      if (features[0] < -1166) {
                                          return 21356;
                                      } else {
                                          return 15462;
                                      }
                                  } else {
                                      if (features[2] < 7278) {
                                          return 14513;
                                      } else {
                                          return 15630;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7352) {
                                      if (features[0] < 1127) {
                                          return 21530;
                                      } else {
                                          return 15655;
                                      }
                                  } else {
                                      if (features[0] < -1451) {
                                          return 23796;
                                      } else {
                                          return 17208;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 692) {
                                  if (features[3] < -2776) {
                                      if (features[2] < 7498) {
                                          return 22848;
                                      } else {
                                          return 25121;
                                      }
                                  } else {
                                      if (features[2] < 7546) {
                                          return 22121;
                                      } else {
                                          return 24228;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7618) {
                                      if (features[0] < 3724) {
                                          return 20346;
                                      } else {
                                          return 18890;
                                      }
                                  } else {
                                      if (features[2] < 7707) {
                                          return 20824;
                                      } else {
                                          return 21839;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7467) {
                              if (features[2] < 7307) {
                                  if (features[0] < 9449) {
                                      if (features[0] < 5550) {
                                          return 14550;
                                      } else {
                                          return 15262;
                                      }
                                  } else {
                                      if (features[2] < 7287) {
                                          return 14110;
                                      } else {
                                          return 14565;
                                      }
                                  }
                              } else {
                                  if (features[3] < -1879) {
                                      if (features[2] < 7328) {
                                          return 19096;
                                      } else {
                                          return 17015;
                                      }
                                  } else {
                                      if (features[0] < 2993) {
                                          return 18806;
                                      } else {
                                          return 16248;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7621) {
                                  if (features[2] < 7577) {
                                      if (features[0] < -1860) {
                                          return 21675;
                                      } else {
                                          return 18462;
                                      }
                                  } else {
                                      if (features[0] < 578) {
                                          return 23571;
                                      } else {
                                          return 19429;
                                      }
                                  }
                              } else {
                                  if (features[0] < 511) {
                                      if (features[0] < -4470) {
                                          return 24149;
                                      } else {
                                          return 24316;
                                      }
                                  } else {
                                      if (features[2] < 7699) {
                                          return 20635;
                                      } else {
                                          return 21439;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[2] < 7942) {
                      if (features[3] < -1910) {
                          if (features[0] < 2085) {
                              if (features[0] < -1474) {
                                  if (features[3] < -5668) {
                                      if (features[3] < -6926) {
                                          return 28242;
                                      } else {
                                          return 28491;
                                      }
                                  } else {
                                      if (features[0] < -7448) {
                                          return 28248;
                                      } else {
                                          return 27358;
                                      }
                                  }
                              } else {
                                  if (features[0] < 723) {
                                      if (features[0] < 691) {
                                          return 23757;
                                      } else {
                                          return 24535;
                                      }
                                  } else {
                                      if (features[2] < 7798) {
                                          return 25095;
                                      } else {
                                          return 26746;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7857) {
                                  if (features[2] < 7763) {
                                      if (features[2] < 7751) {
                                          return 22251;
                                      } else {
                                          return 22713;
                                      }
                                  } else {
                                      if (features[0] < 13122) {
                                          return 23809;
                                      } else {
                                          return 22958;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5884) {
                                      if (features[0] < 10451) {
                                          return 25758;
                                      } else {
                                          return 23658;
                                      }
                                  } else {
                                      if (features[0] < 10072) {
                                          return 24980;
                                      } else {
                                          return 24076;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7793) {
                              if (features[3] < -1767) {
                                  if (features[2] < 7749) {
                                      if (features[0] < 9655) {
                                          return 22124;
                                      } else {
                                          return 21413;
                                      }
                                  } else {
                                      if (features[0] < -1953) {
                                          return 26399;
                                      } else {
                                          return 22766;
                                      }
                                  }
                              } else {
                                  if (features[0] < 13139) {
                                      if (features[3] < -1377) {
                                          return 22140;
                                      } else {
                                          return 21854;
                                      }
                                  } else {
                                      if (features[0] < 13365) {
                                          return 21289;
                                      } else {
                                          return 21581;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 495) {
                                  if (features[2] < 7801) {
                                      if (features[3] < -1874) {
                                          return 26633;
                                      } else {
                                          return 26592;
                                      }
                                  } else {
                                      if (features[3] < -1803) {
                                          return 26747;
                                      } else {
                                          return 26603;
                                      }
                                  }
                              } else {
                                  if (features[0] < 5489) {
                                      if (features[2] < 7916) {
                                          return 24105;
                                      } else {
                                          return 24226;
                                      }
                                  } else {
                                      if (features[0] < 5493) {
                                          return 22679;
                                      } else {
                                          return 23503;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[2] < 8108) {
                          if (features[0] < 3672) {
                              if (features[3] < -2660) {
                                  if (features[0] < 569) {
                                      if (features[3] < -9817) {
                                          return 28815;
                                      } else {
                                          return 28394;
                                      }
                                  } else {
                                      if (features[3] < -5692) {
                                          return 28017;
                                      } else {
                                          return 27643;
                                      }
                                  }
                              } else {
                                  if (features[0] < -4615) {
                                      if (features[3] < -1795) {
                                          return 28520;
                                      } else {
                                          return 28655;
                                      }
                                  } else {
                                      if (features[3] < -2082) {
                                          return 28310;
                                      } else {
                                          return 28447;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 8033) {
                                  if (features[0] < 12274) {
                                      if (features[0] < 5662) {
                                          return 25322;
                                      } else {
                                          return 26184;
                                      }
                                  } else {
                                      if (features[2] < 8008) {
                                          return 24895;
                                      } else {
                                          return 25401;
                                      }
                                  }
                              } else {
                                  if (features[0] < 11890) {
                                      if (features[0] < 5568) {
                                          return 26230;
                                      } else {
                                          return 26994;
                                      }
                                  } else {
                                      if (features[2] < 8069) {
                                          return 25821;
                                      } else {
                                          return 26316;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[3] < -1039) {
                              if (features[0] < 12971) {
                                  if (features[0] < 5471) {
                                      if (features[3] < -5925) {
                                          return 28751;
                                      } else {
                                          return 28551;
                                      }
                                  } else {
                                      if (features[3] < -6865) {
                                          return 28377;
                                      } else {
                                          return 27976;
                                      }
                                  }
                              } else {
                                  if (features[2] < 8161) {
                                      if (features[0] < 13006) {
                                          return 27185;
                                      } else {
                                          return 26911;
                                      }
                                  } else {
                                      if (features[3] < -4543) {
                                          return 27490;
                                      } else {
                                          return 27700;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 8144) {
                                  if (features[0] < -2291) {
                                      return 28798;
                                  } else {
                                      if (features[3] < -1031) {
                                          return 27371;
                                      } else {
                                          return 27369;
                                      }
                                  }
                              } else {
                                  if (features[0] < -5035) {
                                      if (features[2] < 8275) {
                                          return 28874;
                                      } else {
                                          return 28977;
                                      }
                                  } else {
                                      if (features[3] < -465) {
                                          return 28850;
                                      } else {
                                          return 28977;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
        }
        

static inline int32_t model_Nico_allparams_tree_3(const int16 *features, int32_t features_length) {
          if (features[2] < 7257) {
              if (features[2] < 6859) {
                  if (features[3] < -3772) {
                      if (features[0] < -2025) {
                          if (features[0] < -2782) {
                              if (features[2] < 6624) {
                                  if (features[3] < -5516) {
                                      if (features[2] < 6366) {
                                          return 12698;
                                      } else {
                                          return 15084;
                                      }
                                  } else {
                                      if (features[3] < -4664) {
                                          return 12784;
                                      } else {
                                          return 11716;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5934) {
                                      if (features[3] < -6688) {
                                          return 18566;
                                      } else {
                                          return 16903;
                                      }
                                  } else {
                                      if (features[0] < -4331) {
                                          return 16210;
                                      } else {
                                          return 13443;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -9000) {
                                  if (features[0] < -2700) {
                                      if (features[3] < -10874) {
                                          return 17322;
                                      } else {
                                          return 12407;
                                      }
                                  } else {
                                      if (features[3] < -11357) {
                                          return 16781;
                                      } else {
                                          return 15163;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6564) {
                                      if (features[2] < 6251) {
                                          return 12172;
                                      } else {
                                          return 10092;
                                      }
                                  } else {
                                      if (features[0] < -2645) {
                                          return 13320;
                                      } else {
                                          return 12537;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 6702) {
                              if (features[0] < 6591) {
                                  if (features[3] < -6442) {
                                      if (features[2] < 6193) {
                                          return 11887;
                                      } else {
                                          return 8030;
                                      }
                                  } else {
                                      if (features[0] < 2087) {
                                          return 8041;
                                      } else {
                                          return 5735;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6560) {
                                      if (features[2] < 6517) {
                                          return 2981;
                                      } else {
                                          return 3499;
                                      }
                                  } else {
                                      if (features[0] < 11282) {
                                          return 6210;
                                      } else {
                                          return 4017;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 6257) {
                                  if (features[0] < 386) {
                                      if (features[2] < 6856) {
                                          return 17235;
                                      } else {
                                          return 16833;
                                      }
                                  } else {
                                      if (features[2] < 6781) {
                                          return 9286;
                                      } else {
                                          return 10572;
                                      }
                                  }
                              } else {
                                  if (features[3] < -6739) {
                                      if (features[3] < -10426) {
                                          return 9041;
                                      } else {
                                          return 7767;
                                      }
                                  } else {
                                      if (features[3] < -6115) {
                                          return 6749;
                                      } else {
                                          return 6104;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[0] < -534) {
                          if (features[0] < -4724) {
                              if (features[3] < -3152) {
                                  if (features[2] < 6635) {
                                      if (features[2] < 6477) {
                                          return 11600;
                                      } else {
                                          return 12040;
                                      }
                                  } else {
                                      if (features[2] < 6726) {
                                          return 14189;
                                      } else {
                                          return 15487;
                                      }
                                  }
                              } else {
                                  if (features[0] < -8012) {
                                      if (features[3] < -2176) {
                                          return 13150;
                                      } else {
                                          return 11600;
                                      }
                                  } else {
                                      if (features[2] < 6726) {
                                          return 11617;
                                      } else {
                                          return 13940;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -3757) {
                                  if (features[2] < 6778) {
                                      if (features[0] < -4281) {
                                          return 10640;
                                      } else {
                                          return 8988;
                                      }
                                  } else {
                                      if (features[3] < -2669) {
                                          return 12177;
                                      } else {
                                          return 11270;
                                      }
                                  }
                              } else {
                                  if (features[3] < -3175) {
                                      if (features[0] < -2526) {
                                          return 10948;
                                      } else {
                                          return 8791;
                                      }
                                  } else {
                                      if (features[2] < 6589) {
                                          return 8700;
                                      } else {
                                          return 8979;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 6657) {
                              if (features[3] < -1213) {
                                  if (features[0] < 13741) {
                                      if (features[2] < 6466) {
                                          return 3363;
                                      } else {
                                          return 4240;
                                      }
                                  } else {
                                      if (features[3] < -2340) {
                                          return 2490;
                                      } else {
                                          return 1830;
                                      }
                                  }
                              } else {
                                  if (features[3] < -558) {
                                      if (features[2] < 5780) {
                                          return 2921;
                                      } else {
                                          return 2240;
                                      }
                                  } else {
                                      if (features[0] < 3489) {
                                          return 2900;
                                      } else {
                                          return 3216;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 4189) {
                                  if (features[3] < -3056) {
                                      if (features[2] < 6767) {
                                          return 8038;
                                      } else {
                                          return 9852;
                                      }
                                  } else {
                                      if (features[0] < 1073) {
                                          return 7466;
                                      } else {
                                          return 8261;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6809) {
                                      if (features[0] < 10880) {
                                          return 5649;
                                      } else {
                                          return 4665;
                                      }
                                  } else {
                                      if (features[0] < 10440) {
                                          return 6887;
                                      } else {
                                          return 5708;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[2] < 7127) {
                      if (features[0] < 158) {
                          if (features[0] < -4488) {
                              if (features[3] < -4447) {
                                  if (features[3] < -9039) {
                                      if (features[0] < -4913) {
                                          return 24932;
                                      } else {
                                          return 24517;
                                      }
                                  } else {
                                      if (features[0] < -6879) {
                                          return 22050;
                                      } else {
                                          return 20570;
                                      }
                                  }
                              } else {
                                  if (features[2] < 6951) {
                                      if (features[3] < -2748) {
                                          return 17808;
                                      } else {
                                          return 17055;
                                      }
                                  } else {
                                      if (features[0] < -8462) {
                                          return 18615;
                                      } else {
                                          return 19781;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -5273) {
                                  if (features[2] < 6978) {
                                      if (features[2] < 6910) {
                                          return 17966;
                                      } else {
                                          return 17336;
                                      }
                                  } else {
                                      if (features[3] < -8187) {
                                          return 21579;
                                      } else {
                                          return 18994;
                                      }
                                  }
                              } else {
                                  if (features[0] < -3467) {
                                      if (features[2] < 6996) {
                                          return 14366;
                                      } else {
                                          return 15572;
                                      }
                                  } else {
                                      if (features[2] < 6999) {
                                          return 15438;
                                      } else {
                                          return 16754;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 4148) {
                              if (features[2] < 6987) {
                                  if (features[0] < 1432) {
                                      if (features[0] < 1318) {
                                          return 12161;
                                      } else {
                                          return 12660;
                                      }
                                  } else {
                                      if (features[2] < 6922) {
                                          return 12208;
                                      } else {
                                          return 13684;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7062) {
                                      if (features[3] < -5898) {
                                          return 14913;
                                      } else {
                                          return 13869;
                                      }
                                  } else {
                                      if (features[0] < 1423) {
                                          return 14860;
                                      } else {
                                          return 15786;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 12984) {
                                  if (features[0] < 5891) {
                                      if (features[2] < 7006) {
                                          return 7896;
                                      } else {
                                          return 10153;
                                      }
                                  } else {
                                      if (features[2] < 6959) {
                                          return 9162;
                                      } else {
                                          return 11415;
                                      }
                                  }
                              } else {
                                  if (features[3] < -4266) {
                                      if (features[2] < 7001) {
                                          return 8657;
                                      } else {
                                          return 11100;
                                      }
                                  } else {
                                      if (features[2] < 7012) {
                                          return 7550;
                                      } else {
                                          return 10322;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[3] < -4028) {
                          if (features[0] < -457) {
                              if (features[2] < 7167) {
                                  if (features[3] < -4443) {
                                      if (features[0] < -3769) {
                                          return 23104;
                                      } else {
                                          return 20024;
                                      }
                                  } else {
                                      if (features[0] < -5004) {
                                          return 22336;
                                      } else {
                                          return 18786;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7189) {
                                      if (features[2] < 7179) {
                                          return 23167;
                                      } else {
                                          return 23376;
                                      }
                                  } else {
                                      if (features[3] < -4485) {
                                          return 24255;
                                      } else {
                                          return 22679;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -6509) {
                                  if (features[0] < 4481) {
                                      if (features[3] < -7497) {
                                          return 18074;
                                      } else {
                                          return 17042;
                                      }
                                  } else {
                                      if (features[0] < 7368) {
                                          return 15119;
                                      } else {
                                          return 15733;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7194) {
                                      if (features[3] < -5819) {
                                          return 14051;
                                      } else {
                                          return 14587;
                                      }
                                  } else {
                                      if (features[0] < 5766) {
                                          return 17108;
                                      } else {
                                          return 14943;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 3755) {
                              if (features[3] < -3135) {
                                  if (features[2] < 7187) {
                                      if (features[0] < -5139) {
                                          return 22195;
                                      } else {
                                          return 17109;
                                      }
                                  } else {
                                      if (features[2] < 7218) {
                                          return 20355;
                                      } else {
                                          return 18046;
                                      }
                                  }
                              } else {
                                  if (features[0] < -1397) {
                                      if (features[3] < -2525) {
                                          return 17550;
                                      } else {
                                          return 16683;
                                      }
                                  } else {
                                      if (features[2] < 7208) {
                                          return 15105;
                                      } else {
                                          return 16784;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7190) {
                                  if (features[0] < 13068) {
                                      if (features[3] < -2827) {
                                          return 13540;
                                      } else {
                                          return 12912;
                                      }
                                  } else {
                                      if (features[2] < 7153) {
                                          return 11527;
                                      } else {
                                          return 12351;
                                      }
                                  }
                              } else {
                                  if (features[0] < 9859) {
                                      if (features[0] < 5714) {
                                          return 13476;
                                      } else {
                                          return 14746;
                                      }
                                  } else {
                                      if (features[2] < 7237) {
                                          return 13227;
                                      } else {
                                          return 13924;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          } else {
              if (features[0] < 1120) {
                  if (features[2] < 7505) {
                      if (features[0] < -4551) {
                          if (features[2] < 7395) {
                              if (features[2] < 7353) {
                                  if (features[3] < -3992) {
                                      if (features[3] < -5608) {
                                          return 26065;
                                      } else {
                                          return 25286;
                                      }
                                  } else {
                                      if (features[3] < -2938) {
                                          return 24328;
                                      } else {
                                          return 23447;
                                      }
                                  }
                              } else {
                                  if (features[3] < -4552) {
                                      if (features[2] < 7364) {
                                          return 26477;
                                      } else {
                                          return 26876;
                                      }
                                  } else {
                                      if (features[0] < -6865) {
                                          return 24929;
                                      } else {
                                          return 24179;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -7671) {
                                  if (features[0] < -8225) {
                                      if (features[3] < -6819) {
                                          return 27642;
                                      } else {
                                          return 27412;
                                      }
                                  } else {
                                      if (features[2] < 7475) {
                                          return 26697;
                                      } else {
                                          return 27046;
                                      }
                                  }
                              } else {
                                  if (features[3] < -4461) {
                                      if (features[0] < -6096) {
                                          return 25846;
                                      } else {
                                          return 26563;
                                      }
                                  } else {
                                      if (features[3] < -3579) {
                                          return 24246;
                                      } else {
                                          return 25041;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7431) {
                              if (features[0] < -628) {
                                  if (features[2] < 7344) {
                                      if (features[3] < -4614) {
                                          return 22348;
                                      } else {
                                          return 20113;
                                      }
                                  } else {
                                      if (features[2] < 7355) {
                                          return 22317;
                                      } else {
                                          return 23143;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7366) {
                                      if (features[0] < 903) {
                                          return 17474;
                                      } else {
                                          return 18230;
                                      }
                                  } else {
                                      if (features[0] < 899) {
                                          return 18522;
                                      } else {
                                          return 19323;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < -1131) {
                                  if (features[0] < -3865) {
                                      if (features[3] < -2452) {
                                          return 22787;
                                      } else {
                                          return 21843;
                                      }
                                  } else {
                                      if (features[2] < 7474) {
                                          return 23624;
                                      } else {
                                          return 25154;
                                      }
                                  }
                              } else {
                                  if (features[0] < 915) {
                                      if (features[2] < 7485) {
                                          return 19070;
                                      } else {
                                          return 19594;
                                      }
                                  } else {
                                      if (features[3] < -2758) {
                                          return 20498;
                                      } else {
                                          return 20017;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[2] < 7802) {
                          if (features[2] < 7645) {
                              if (features[3] < -3314) {
                                  if (features[3] < -5743) {
                                      if (features[0] < -7521) {
                                          return 27957;
                                      } else {
                                          return 26999;
                                      }
                                  } else {
                                      if (features[0] < -1129) {
                                          return 25913;
                                      } else {
                                          return 23035;
                                      }
                                  }
                              } else {
                                  if (features[0] < -1111) {
                                      if (features[2] < 7541) {
                                          return 26485;
                                      } else {
                                          return 24374;
                                      }
                                  } else {
                                      if (features[2] < 7580) {
                                          return 20819;
                                      } else {
                                          return 23110;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -3048) {
                                  if (features[3] < -5506) {
                                      if (features[0] < -8290) {
                                          return 28317;
                                      } else {
                                          return 27528;
                                      }
                                  } else {
                                      if (features[2] < 7774) {
                                          return 26409;
                                      } else {
                                          return 25892;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7772) {
                                      if (features[0] < -1509) {
                                          return 26612;
                                      } else {
                                          return 24154;
                                      }
                                  } else {
                                      if (features[2] < 7782) {
                                          return 25858;
                                      } else {
                                          return 26809;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[0] < 826) {
                              if (features[3] < -1682) {
                                  if (features[0] < -4514) {
                                      if (features[3] < -6030) {
                                          return 28730;
                                      } else {
                                          return 28414;
                                      }
                                  } else {
                                      if (features[0] < -1952) {
                                          return 27701;
                                      } else {
                                          return 28297;
                                      }
                                  }
                              } else {
                                  if (features[3] < -746) {
                                      if (features[0] < 483) {
                                          return 28765;
                                      } else {
                                          return 28678;
                                      }
                                  } else {
                                      if (features[3] < -345) {
                                          return 28889;
                                      } else {
                                          return 28982;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7867) {
                                  if (features[2] < 7844) {
                                      if (features[2] < 7834) {
                                          return 26371;
                                      } else {
                                          return 26484;
                                      }
                                  } else {
                                      if (features[3] < -5336) {
                                          return 27112;
                                      } else {
                                          return 26490;
                                      }
                                  }
                              } else {
                                  if (features[0] < 915) {
                                      if (features[2] < 7975) {
                                          return 27365;
                                      } else {
                                          return 27957;
                                      }
                                  } else {
                                      if (features[2] < 7944) {
                                          return 27037;
                                      } else {
                                          return 27709;
                                      }
                                  }
                              }
                          }
                      }
                  }
              } else {
                  if (features[0] < 13116) {
                      if (features[3] < -848) {
                          if (features[2] < 7713) {
                              if (features[3] < -3368) {
                                  if (features[2] < 7435) {
                                      if (features[3] < -6190) {
                                          return 19175;
                                      } else {
                                          return 17462;
                                      }
                                  } else {
                                      if (features[2] < 7566) {
                                          return 20653;
                                      } else {
                                          return 22601;
                                      }
                                  }
                              } else {
                                  if (features[3] < -1975) {
                                      if (features[0] < 6710) {
                                          return 18913;
                                      } else {
                                          return 16076;
                                      }
                                  } else {
                                      if (features[0] < 6464) {
                                          return 18084;
                                      } else {
                                          return 15543;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 7925) {
                                  if (features[0] < 3821) {
                                      if (features[2] < 7784) {
                                          return 25192;
                                      } else {
                                          return 26211;
                                      }
                                  } else {
                                      if (features[2] < 7813) {
                                          return 22641;
                                      } else {
                                          return 24396;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5469) {
                                      if (features[2] < 8113) {
                                          return 27164;
                                      } else {
                                          return 28356;
                                      }
                                  } else {
                                      if (features[2] < 8096) {
                                          return 26015;
                                      } else {
                                          return 27843;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 8354) {
                              if (features[3] < -645) {
                                  if (features[0] < 5370) {
                                      if (features[2] < 8333) {
                                          return 28833;
                                      } else {
                                          return 28858;
                                      }
                                  } else {
                                      if (features[3] < -743) {
                                          return 28852;
                                      } else {
                                          return 28867;
                                      }
                                  }
                              } else {
                                  if (features[0] < 12781) {
                                      if (features[2] < 8349) {
                                          return 28893;
                                      } else {
                                          return 28909;
                                      }
                                  } else {
                                      if (features[2] < 8338) {
                                          return 28896;
                                      } else {
                                          return 28922;
                                      }
                                  }
                              }
                          } else {
                              if (features[3] < -192) {
                                  if (features[3] < -305) {
                                      if (features[3] < -402) {
                                          return 28921;
                                      } else {
                                          return 28939;
                                      }
                                  } else {
                                      if (features[3] < -251) {
                                          return 28949;
                                      } else {
                                          return 28963;
                                      }
                                  }
                              } else {
                                  if (features[3] < -85) {
                                      if (features[2] < 8368) {
                                          return 28975;
                                      } else {
                                          return 28980;
                                      }
                                  } else {
                                      if (features[2] < 8373) {
                                          return 28997;
                                      } else {
                                          return 28999;
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[2] < 7667) {
                          if (features[0] < 13168) {
                              if (features[3] < -1787) {
                                  if (features[0] < 13134) {
                                      if (features[2] < 7314) {
                                          return 14848;
                                      } else {
                                          return 15471;
                                      }
                                  } else {
                                      if (features[3] < -3418) {
                                          return 17462;
                                      } else {
                                          return 15847;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7518) {
                                      if (features[2] < 7436) {
                                          return 15904;
                                      } else {
                                          return 17387;
                                      }
                                  } else {
                                      if (features[3] < -1442) {
                                          return 18899;
                                      } else {
                                          return 19196;
                                      }
                                  }
                              }
                          } else {
                              if (features[0] < 13968) {
                                  if (features[0] < 13745) {
                                      if (features[0] < 13216) {
                                          return 18068;
                                      } else {
                                          return 17577;
                                      }
                                  } else {
                                      if (features[2] < 7553) {
                                          return 18115;
                                      } else {
                                          return 20142;
                                      }
                                  }
                              } else {
                                  if (features[3] < -5911) {
                                      if (features[3] < -6598) {
                                          return 20791;
                                      } else {
                                          return 20691;
                                      }
                                  } else {
                                      if (features[0] < 14028) {
                                          return 20366;
                                      } else {
                                          return 20487;
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[2] < 7940) {
                              if (features[2] < 7796) {
                                  if (features[3] < -4636) {
                                      if (features[0] < 13146) {
                                          return 22476;
                                      } else {
                                          return 21876;
                                      }
                                  } else {
                                      if (features[0] < 13688) {
                                          return 21578;
                                      } else {
                                          return 21085;
                                      }
                                  }
                              } else {
                                  if (features[2] < 7853) {
                                      if (features[2] < 7832) {
                                          return 22880;
                                      } else {
                                          return 23305;
                                      }
                                  } else {
                                      if (features[2] < 7913) {
                                          return 23821;
                                      } else {
                                          return 24203;
                                      }
                                  }
                              }
                          } else {
                              if (features[2] < 8077) {
                                  if (features[2] < 7998) {
                                      if (features[3] < -2635) {
                                          return 24581;
                                      } else {
                                          return 24828;
                                      }
                                  } else {
                                      if (features[0] < 13130) {
                                          return 25668;
                                      } else {
                                          return 25306;
                                      }
                                  }
                              } else {
                                  if (features[2] < 8142) {
                                      if (features[2] < 8108) {
                                          return 26376;
                                      } else {
                                          return 26847;
                                      }
                                  } else {
                                      if (features[2] < 8184) {
                                          return 27296;
                                      } else {
                                          return 27785;
                                      }
                                  }
                              }
                          }
                      }
                  }
              }
          }
        }
        

static const uint8_t model_Nico_allparams_leaves[3884] = { 0, 212, 75, 70, 0, 76, 115, 70, 0, 232, 107, 70, 0, 148, 76, 70, 0, 204, 74, 70, 0, 96, 66, 70, 0, 4, 61, 70, 0, 180, 54, 70, 0, 20, 64, 70, 0, 172, 89, 70, 0, 44, 99, 70, 0, 48, 126, 70, 0, 252, 15, 70, 0, 144, 25, 70, 0, 132, 17, 70, 0, 96, 46, 70, 0, 164, 93, 70, 0, 236, 74, 70, 0, 176, 93, 70, 0, 70, 146, 70, 0, 56, 151, 70, 0, 44, 139, 70, 0, 120, 124, 70, 0, 108, 108, 70, 0, 230, 149, 70, 0, 96, 119, 70, 0, 128, 18, 70, 0, 196, 57, 70, 0, 116, 138, 70, 0, 96, 149, 70, 0, 104, 89, 70, 0, 120, 49, 70, 0, 96, 115, 69, 0, 104, 144, 69, 0, 112, 238, 69, 0, 80, 192, 69, 0, 136, 28, 70, 0, 240, 211, 69, 0, 116, 7, 70, 0, 176, 201, 69, 0, 48, 56, 69, 0, 112, 71, 69, 0, 192, 79, 69, 0, 64, 141, 69, 0, 200, 231, 69, 0, 96, 169, 69, 0, 64, 196, 69, 0, 152, 215, 69, 0, 0, 16, 69, 0, 0, 110, 69, 0, 80, 71, 69, 0, 48, 15, 69, 0, 184, 137, 69, 0, 128, 148, 69, 0, 88, 201, 69, 0, 40, 172, 69, 0, 96, 200, 68, 0, 192, 51, 69, 0, 224, 91, 69, 0, 120, 158, 69, 0, 96, 130, 68, 0, 224, 239, 68, 0, 96, 77, 69, 0, 168, 152, 69, 0, 166, 177, 70, 0, 48, 198, 70, 0, 52, 181, 70, 0, 124, 158, 70, 0, 70, 167, 70, 0, 24, 153, 70, 0, 134, 183, 70, 0, 186, 177, 70, 0, 82, 155, 70, 0, 110, 139, 70, 0, 62, 143, 70, 0, 64, 129, 70, 0, 158, 157, 70, 0, 68, 149, 70, 0, 80, 165, 70, 0, 112, 153, 70, 0, 220, 134, 70, 0, 254, 145, 70, 0, 50, 145, 70, 0, 184, 149, 70, 0, 62, 140, 70, 0, 192, 153, 70, 0, 18, 169, 70, 0, 102, 189, 70, 0, 220, 89, 70, 0, 88, 106, 70, 0, 172, 87, 70, 0, 4, 123, 70, 0, 208, 127, 70, 0, 48, 142, 70, 0, 248, 132, 70, 0, 240, 96, 70, 0, 32, 115, 70, 0, 224, 93, 70, 0, 164, 113, 70, 0, 128, 109, 70, 0, 124, 126, 70, 0, 214, 129, 70, 0, 220, 100, 70, 0, 220, 83, 70, 0, 168, 87, 70, 0, 172, 97, 70, 0, 140, 93, 70, 0, 40, 138, 70, 0, 178, 140, 70, 0, 112, 93, 70, 0, 36, 91, 70, 0, 12, 10, 70, 0, 192, 46, 70, 0, 208, 75, 70, 0, 32, 98, 70, 0, 24, 43, 70, 0, 136, 71, 70, 0, 228, 32, 70, 0, 132, 12, 70, 0, 32, 252, 69, 0, 8, 222, 69, 0, 132, 31, 70, 0, 116, 12, 70, 0, 44, 54, 70, 0, 124, 82, 70, 0, 76, 48, 70, 0, 60, 50, 70, 0, 222, 207, 70, 0, 164, 197, 70, 0, 250, 191, 70, 0, 60, 183, 70, 0, 20, 215, 70, 0, 160, 210, 70, 0, 160, 218, 70, 0, 194, 222, 70, 0, 224, 179, 70, 0, 140, 222, 70, 0, 204, 208, 70, 0, 178, 222, 70, 0, 74, 223, 70, 0, 224, 223, 70, 0, 142, 224, 70, 0, 234, 224, 70, 0, 138, 175, 70, 0, 20, 168, 70, 0, 50, 187, 70, 0, 28, 156, 70, 0, 226, 155, 70, 0, 16, 148, 70, 0, 180, 171, 70, 0, 64, 159, 70, 0, 46, 195, 70, 0, 248, 177, 70, 0, 162, 205, 70, 0, 192, 192, 70, 0, 244, 214, 70, 0, 24, 222, 70, 0, 168, 206, 70, 0, 74, 213, 70, 0, 140, 155, 70, 0, 224, 188, 70, 0, 42, 150, 70, 0, 160, 168, 70, 0, 66, 168, 70, 0, 162, 139, 70, 0, 44, 135, 70, 0, 156, 163, 70, 0, 178, 128, 70, 0, 172, 101, 70, 0, 76, 125, 70, 0, 106, 162, 70, 0, 186, 146, 70, 0, 170, 161, 70, 0, 196, 164, 70, 0, 18, 198, 70, 0, 154, 205, 70, 0, 114, 195, 70, 0, 36, 199, 70, 0, 210, 171, 70, 0, 78, 177, 70, 0, 250, 182, 70, 0, 44, 191, 70, 0, 216, 210, 70, 0, 134, 195, 70, 0, 56, 198, 70, 0, 224, 204, 70, 0, 172, 216, 70, 0, 98, 222, 70, 0, 34, 213, 70, 0, 200, 207, 70, 0, 50, 169, 70, 0, 48, 169, 70, 0, 52, 169, 70, 0, 108, 169, 70, 0, 106, 169, 70, 0, 220, 169, 70, 0, 222, 169, 70, 0, 224, 169, 70, 0, 218, 169, 70, 0, 130, 169, 70, 0, 88, 169, 70, 0, 76, 169, 70, 0, 100, 169, 70, 0, 196, 169, 70, 0, 200, 169, 70, 0, 202, 169, 70, 0, 208, 169, 70, 0, 4, 225, 70, 0, 36, 225, 70, 0, 72, 225, 70, 0, 104, 225, 70, 0, 84, 225, 70, 0, 110, 225, 70, 0, 134, 225, 70, 0, 108, 225, 70, 0, 148, 225, 70, 0, 168, 225, 70, 0, 164, 225, 70, 0, 180, 225, 70, 0, 194, 225, 70, 0, 208, 225, 70, 0, 222, 225, 70, 0, 238, 225, 70, 0, 20, 226, 70, 0, 252, 225, 70, 0, 64, 226, 70, 0, 42, 226, 70, 0, 100, 226, 70, 0, 110, 226, 70, 0, 132, 226, 70, 0, 140, 226, 70, 0, 2, 226, 70, 0, 44, 226, 70, 0, 68, 226, 70, 0, 102, 226, 70, 0, 94, 226, 70, 0, 120, 54, 70, 0, 100, 57, 70, 0, 156, 78, 70, 0, 24, 61, 70, 0, 20, 63, 70, 0, 124, 74, 70, 0, 60, 111, 70, 0, 188, 65, 70, 0, 76, 71, 70, 0, 116, 125, 70, 0, 0, 76, 70, 0, 196, 56, 70, 0, 220, 51, 70, 0, 160, 21, 70, 0, 96, 20, 70, 0, 164, 8, 70, 0, 40, 146, 70, 0, 160, 115, 70, 0, 244, 148, 70, 0, 108, 132, 70, 0, 164, 99, 70, 0, 0, 70, 70, 0, 204, 95, 70, 0, 64, 53, 70, 0, 232, 149, 70, 0, 100, 119, 70, 0, 160, 55, 70, 0, 240, 7, 70, 0, 76, 165, 70, 0, 168, 141, 70, 0, 112, 89, 70, 0, 136, 49, 70, 0, 0, 94, 69, 0, 40, 223, 69, 0, 116, 22, 70, 0, 240, 189, 69, 0, 76, 30, 70, 0, 44, 9, 70, 0, 120, 50, 70, 0, 228, 33, 70, 0, 64, 221, 69, 0, 120, 154, 69, 0, 96, 99, 69, 0, 0, 41, 69, 0, 248, 226, 69, 0, 88, 169, 69, 0, 248, 243, 69, 0, 112, 218, 69, 0, 96, 87, 69, 0, 120, 150, 69, 0, 32, 68, 69, 0, 16, 164, 69, 0, 96, 253, 68, 0, 192, 186, 68, 0, 208, 56, 69, 0, 64, 83, 69, 0, 200, 230, 69, 0, 224, 251, 69, 0, 188, 34, 70, 0, 88, 21, 70, 0, 192, 167, 69, 0, 152, 211, 69, 0, 176, 161, 69, 0, 184, 200, 69, 0, 136, 149, 70, 0, 66, 159, 70, 0, 162, 165, 70, 0, 190, 175, 70, 0, 92, 133, 70, 0, 116, 147, 70, 0, 50, 129, 70, 0, 80, 137, 70, 0, 66, 183, 70, 0, 62, 175, 70, 0, 74, 198, 70, 0, 148, 183, 70, 0, 114, 157, 70, 0, 58, 149, 70, 0, 128, 159, 70, 0, 200, 106, 70, 0, 78, 129, 70, 0, 106, 141, 70, 0, 148, 133, 70, 0, 156, 93, 70, 0, 160, 100, 70, 0, 110, 151, 70, 0, 116, 115, 70, 0, 244, 149, 70, 0, 116, 124, 70, 0, 98, 146, 70, 0, 238, 132, 70, 0, 4, 172, 70, 0, 164, 144, 70, 0, 118, 167, 70, 0, 132, 144, 70, 0, 252, 110, 70, 0, 120, 100, 70, 0, 204, 120, 70, 0, 52, 91, 70, 0, 84, 54, 70, 0, 48, 70, 70, 0, 252, 86, 70, 0, 192, 103, 70, 0, 160, 29, 70, 0, 96, 67, 70, 0, 200, 0, 70, 0, 232, 37, 70, 0, 136, 239, 69, 0, 136, 36, 70, 0, 232, 251, 69, 0, 56, 32, 70, 0, 200, 128, 70, 0, 110, 136, 70, 0, 140, 120, 70, 0, 4, 108, 70, 0, 218, 144, 70, 0, 142, 140, 70, 0, 172, 131, 70, 0, 146, 134, 70, 0, 236, 67, 70, 0, 200, 84, 70, 0, 12, 73, 70, 0, 192, 59, 70, 0, 160, 82, 70, 0, 88, 108, 70, 0, 144, 80, 70, 0, 252, 90, 70, 0, 164, 205, 70, 0, 90, 197, 70, 0, 188, 210, 70, 0, 124, 199, 70, 0, 120, 163, 70, 0, 70, 182, 70, 0, 84, 195, 70, 0, 164, 179, 70, 0, 196, 219, 70, 0, 52, 216, 70, 0, 242, 210, 70, 0, 176, 204, 70, 0, 84, 187, 70, 0, 106, 198, 70, 0, 208, 207, 70, 0, 180, 201, 70, 0, 200, 178, 70, 0, 32, 147, 70, 0, 76, 168, 70, 0, 94, 152, 70, 0, 212, 176, 70, 0, 72, 184, 70, 0, 184, 164, 70, 0, 112, 173, 70, 0, 64, 204, 70, 0, 152, 196, 70, 0, 56, 210, 70, 0, 14, 216, 70, 0, 42, 188, 70, 0, 172, 184, 70, 0, 250, 194, 70, 0, 130, 189, 70, 0, 244, 168, 70, 0, 212, 163, 70, 0, 146, 146, 70, 0, 126, 155, 70, 0, 182, 193, 70, 0, 164, 180, 70, 0, 80, 179, 70, 0, 214, 172, 70, 0, 28, 149, 70, 0, 156, 136, 70, 0, 82, 168, 70, 0, 248, 163, 70, 0, 124, 148, 70, 0, 58, 152, 70, 0, 158, 155, 70, 0, 16, 159, 70, 0, 224, 136, 70, 0, 156, 148, 70, 0, 88, 131, 70, 0, 124, 125, 70, 0, 186, 148, 70, 0, 254, 156, 70, 0, 250, 166, 70, 0, 70, 132, 70, 0, 184, 104, 70, 0, 46, 129, 70, 0, 228, 140, 70, 0, 0, 149, 70, 0, 152, 158, 70, 0, 250, 165, 70, 0, 36, 213, 70, 0, 192, 194, 70, 0, 32, 174, 70, 0, 82, 169, 70, 0, 52, 196, 70, 0, 14, 174, 70, 0, 184, 195, 70, 0, 150, 174, 70, 0, 254, 220, 70, 0, 76, 212, 70, 0, 32, 192, 70, 0, 222, 202, 70, 0, 48, 187, 70, 0, 134, 181, 70, 0, 180, 172, 70, 0, 58, 180, 70, 0, 58, 224, 70, 0, 210, 221, 70, 0, 210, 215, 70, 0, 10, 213, 70, 0, 248, 195, 70, 0, 184, 199, 70, 0, 194, 186, 70, 0, 190, 215, 70, 0, 90, 217, 70, 0, 222, 221, 70, 0, 2, 193, 70, 0, 230, 189, 70, 0, 60, 184, 70, 0, 138, 186, 70, 0, 74, 225, 70, 0, 12, 224, 70, 0, 128, 223, 70, 0, 46, 221, 70, 0, 186, 218, 70, 0, 202, 217, 70, 0, 54, 215, 70, 0, 90, 210, 70, 0, 236, 225, 70, 0, 8, 224, 70, 0, 44, 222, 70, 0, 90, 224, 70, 0, 0, 225, 70, 0, 80, 225, 70, 0, 52, 226, 70, 0, 130, 207, 70, 0, 174, 215, 70, 0, 162, 212, 70, 0, 66, 223, 70, 0, 24, 221, 70, 0, 146, 219, 70, 0, 216, 207, 70, 0, 0, 201, 70, 0, 2, 198, 70, 0, 92, 204, 70, 0, 8, 213, 70, 0, 202, 216, 70, 0, 114, 220, 70, 0, 228, 224, 70, 0, 88, 123, 70, 0, 104, 150, 70, 0, 152, 122, 70, 0, 64, 99, 70, 0, 44, 80, 70, 0, 82, 142, 70, 0, 184, 78, 70, 0, 176, 114, 70, 0, 8, 68, 70, 0, 148, 119, 70, 0, 170, 134, 70, 0, 210, 130, 70, 0, 88, 31, 70, 0, 196, 70, 70, 0, 52, 20, 70, 0, 176, 38, 70, 0, 88, 183, 69, 0, 160, 208, 69, 0, 228, 4, 70, 0, 32, 225, 69, 0, 48, 137, 69, 0, 96, 0, 69, 0, 208, 199, 69, 0, 176, 85, 69, 0, 172, 19, 70, 0, 128, 251, 69, 0, 224, 244, 69, 0, 208, 179, 69, 0, 244, 42, 70, 0, 188, 53, 70, 0, 40, 7, 70, 0, 216, 210, 69, 0, 106, 152, 70, 0, 244, 143, 70, 0, 202, 173, 70, 0, 148, 142, 70, 0, 204, 139, 70, 0, 156, 125, 70, 0, 6, 157, 70, 0, 132, 130, 70, 0, 40, 185, 70, 0, 174, 198, 70, 0, 246, 176, 70, 0, 46, 193, 70, 0, 120, 152, 70, 0, 224, 162, 70, 0, 36, 157, 70, 0, 34, 163, 70, 0, 128, 66, 70, 0, 212, 21, 70, 0, 144, 92, 70, 0, 76, 58, 70, 0, 36, 128, 70, 0, 140, 137, 70, 0, 30, 129, 70, 0, 124, 93, 70, 0, 232, 252, 69, 0, 244, 18, 70, 0, 156, 36, 70, 0, 64, 65, 70, 0, 232, 222, 69, 0, 24, 4, 70, 0, 16, 67, 70, 0, 48, 59, 70, 0, 236, 7, 70, 0, 60, 54, 70, 0, 80, 126, 69, 0, 0, 3, 69, 0, 240, 100, 69, 0, 16, 85, 69, 0, 176, 59, 69, 0, 160, 96, 69, 0, 96, 129, 68, 0, 64, 162, 68, 0, 0, 205, 68, 0, 96, 240, 68, 0, 128, 77, 70, 0, 120, 48, 70, 0, 24, 136, 70, 0, 12, 80, 70, 0, 152, 48, 70, 0, 8, 13, 70, 0, 28, 10, 70, 0, 96, 245, 69, 0, 88, 181, 69, 0, 64, 31, 69, 0, 8, 183, 69, 0, 80, 92, 69, 0, 240, 1, 70, 0, 24, 166, 69, 0, 216, 198, 69, 0, 176, 223, 69, 0, 240, 135, 70, 0, 76, 148, 70, 0, 134, 156, 70, 0, 246, 159, 70, 0, 40, 71, 70, 0, 144, 100, 70, 0, 126, 132, 70, 0, 12, 123, 70, 0, 76, 1, 70, 0, 196, 39, 70, 0, 12, 67, 70, 0, 60, 90, 70, 0, 220, 26, 70, 0, 184, 16, 70, 0, 120, 230, 69, 0, 52, 10, 70, 0, 16, 103, 70, 0, 104, 88, 70, 0, 180, 15, 70, 0, 128, 232, 69, 0, 116, 48, 70, 0, 52, 41, 70, 0, 36, 65, 70, 0, 152, 84, 70, 0, 48, 234, 69, 0, 160, 22, 70, 0, 64, 234, 69, 0, 96, 215, 69, 0, 60, 41, 70, 0, 156, 53, 70, 0, 36, 94, 70, 0, 28, 73, 70, 0, 238, 210, 70, 0, 244, 192, 70, 0, 174, 136, 70, 0, 228, 155, 70, 0, 56, 168, 70, 0, 56, 216, 70, 0, 4, 167, 70, 0, 182, 219, 70, 0, 202, 213, 70, 0, 136, 188, 70, 0, 44, 199, 70, 0, 212, 179, 70, 0, 246, 167, 70, 0, 190, 197, 70, 0, 102, 170, 70, 0, 30, 128, 70, 0, 200, 138, 70, 0, 222, 210, 70, 0, 226, 185, 70, 0, 66, 146, 70, 0, 234, 151, 70, 0, 250, 214, 70, 0, 248, 200, 70, 0, 16, 204, 70, 0, 242, 184, 70, 0, 16, 173, 70, 0, 156, 154, 70, 0, 50, 188, 70, 0, 48, 166, 70, 0, 216, 166, 70, 0, 152, 113, 70, 0, 196, 98, 70, 0, 56, 116, 70, 0, 52, 168, 70, 0, 156, 116, 70, 0, 232, 185, 70, 0, 112, 134, 70, 0, 128, 178, 70, 0, 66, 196, 70, 0, 210, 172, 70, 0, 72, 189, 70, 0, 244, 158, 70, 0, 148, 147, 70, 0, 176, 162, 70, 0, 158, 170, 70, 0, 88, 99, 70, 0, 120, 110, 70, 0, 120, 92, 70, 0, 148, 99, 70, 0, 48, 149, 70, 0, 236, 146, 70, 0, 224, 125, 70, 0, 86, 169, 70, 0, 60, 144, 70, 0, 38, 184, 70, 0, 202, 151, 70, 0, 170, 188, 70, 0, 248, 189, 70, 0, 54, 161, 70, 0, 126, 167, 70, 0, 164, 220, 70, 0, 150, 222, 70, 0, 176, 220, 70, 0, 188, 213, 70, 0, 154, 185, 70, 0, 174, 191, 70, 0, 14, 196, 70, 0, 244, 208, 70, 0, 214, 173, 70, 0, 114, 177, 70, 0, 2, 186, 70, 0, 92, 179, 70, 0, 60, 201, 70, 0, 212, 184, 70, 0, 40, 195, 70, 0, 24, 188, 70, 0, 216, 172, 70, 0, 74, 167, 70, 0, 62, 206, 70, 0, 220, 177, 70, 0, 248, 172, 70, 0, 188, 170, 70, 0, 82, 166, 70, 0, 154, 168, 70, 0, 18, 208, 70, 0, 192, 207, 70, 0, 246, 208, 70, 0, 214, 207, 70, 0, 82, 188, 70, 0, 68, 189, 70, 0, 46, 177, 70, 0, 158, 183, 70, 0, 30, 225, 70, 0, 212, 221, 70, 0, 226, 218, 70, 0, 246, 215, 70, 0, 208, 222, 70, 0, 222, 223, 70, 0, 44, 221, 70, 0, 62, 222, 70, 0, 212, 197, 70, 0, 144, 204, 70, 0, 126, 194, 70, 0, 114, 198, 70, 0, 236, 204, 70, 0, 228, 210, 70, 0, 186, 201, 70, 0, 152, 205, 70, 0, 158, 224, 70, 0, 14, 223, 70, 0, 178, 221, 70, 0, 144, 218, 70, 0, 98, 212, 70, 0, 62, 210, 70, 0, 196, 214, 70, 0, 104, 216, 70, 0, 252, 224, 70, 0, 214, 213, 70, 0, 210, 213, 70, 0, 98, 226, 70, 0, 100, 225, 70, 0, 104, 70, 70, 0, 176, 107, 70, 0, 192, 71, 70, 0, 16, 55, 70, 0, 12, 145, 70, 0, 14, 132, 70, 0, 72, 125, 70, 0, 12, 82, 70, 0, 84, 135, 70, 0, 220, 65, 70, 0, 26, 131, 70, 0, 236, 108, 70, 0, 48, 62, 70, 0, 176, 29, 70, 0, 32, 80, 70, 0, 228, 67, 70, 0, 188, 57, 70, 0, 240, 250, 69, 0, 72, 251, 69, 0, 56, 179, 69, 0, 80, 58, 69, 0, 176, 90, 69, 0, 16, 194, 69, 0, 16, 123, 69, 0, 166, 134, 70, 0, 130, 131, 70, 0, 24, 17, 70, 0, 48, 37, 70, 0, 68, 13, 70, 0, 184, 242, 69, 0, 232, 210, 69, 0, 192, 190, 69, 0, 32, 60, 70, 0, 180, 93, 70, 0, 252, 113, 70, 0, 120, 77, 70, 0, 132, 53, 70, 0, 208, 89, 70, 0, 64, 38, 70, 0, 112, 12, 70, 0, 68, 62, 70, 0, 24, 48, 70, 0, 16, 43, 70, 0, 92, 9, 70, 0, 76, 12, 70, 0, 48, 82, 69, 0, 128, 132, 69, 0, 160, 27, 69, 0, 192, 228, 68, 0, 144, 54, 69, 0, 0, 12, 69, 0, 64, 53, 69, 0, 0, 73, 69, 0, 48, 251, 69, 0, 240, 25, 70, 0, 80, 233, 69, 0, 20, 1, 70, 0, 136, 176, 69, 0, 200, 145, 69, 0, 56, 215, 69, 0, 96, 178, 69, 0, 200, 194, 70, 0, 138, 191, 70, 0, 68, 172, 70, 0, 180, 160, 70, 0, 32, 139, 70, 0, 62, 133, 70, 0, 110, 145, 70, 0, 138, 154, 70, 0, 92, 140, 70, 0, 112, 135, 70, 0, 150, 168, 70, 0, 100, 148, 70, 0, 120, 96, 70, 0, 80, 115, 70, 0, 56, 113, 70, 0, 228, 130, 70, 0, 4, 62, 70, 0, 208, 69, 70, 0, 192, 62, 70, 0, 208, 85, 70, 0, 4, 105, 70, 0, 180, 88, 70, 0, 48, 104, 70, 0, 168, 118, 70, 0, 192, 246, 69, 0, 164, 30, 70, 0, 40, 15, 70, 0, 92, 50, 70, 0, 68, 7, 70, 0, 112, 45, 70, 0, 240, 235, 69, 0, 72, 33, 70, 0, 128, 180, 70, 0, 112, 156, 70, 0, 128, 174, 70, 0, 196, 146, 70, 0, 254, 180, 70, 0, 160, 182, 70, 0, 126, 189, 70, 0, 52, 141, 70, 0, 36, 133, 70, 0, 60, 108, 70, 0, 212, 117, 70, 0, 140, 91, 70, 0, 236, 99, 70, 0, 168, 133, 70, 0, 124, 105, 70, 0, 102, 173, 70, 0, 170, 133, 70, 0, 6, 159, 70, 0, 252, 140, 70, 0, 28, 137, 70, 0, 86, 130, 70, 0, 32, 131, 70, 0, 144, 83, 70, 0, 192, 73, 70, 0, 28, 52, 70, 0, 252, 64, 70, 0, 144, 82, 70, 0, 104, 102, 70, 0, 172, 78, 70, 0, 144, 89, 70, 0, 162, 203, 70, 0, 140, 197, 70, 0, 16, 190, 70, 0, 46, 183, 70, 0, 218, 206, 70, 0, 248, 209, 70, 0, 194, 194, 70, 0, 230, 188, 70, 0, 244, 215, 70, 0, 40, 214, 70, 0, 146, 208, 70, 0, 76, 211, 70, 0, 236, 201, 70, 0, 134, 207, 70, 0, 108, 189, 70, 0, 162, 195, 70, 0, 152, 174, 70, 0, 34, 157, 70, 0, 90, 174, 70, 0, 206, 180, 70, 0, 132, 136, 70, 0, 108, 142, 70, 0, 180, 144, 70, 0, 246, 150, 70, 0, 6, 178, 70, 0, 166, 170, 70, 0, 144, 184, 70, 0, 132, 196, 70, 0, 252, 148, 70, 0, 20, 153, 70, 0, 36, 160, 70, 0, 98, 156, 70, 0, 106, 218, 70, 0, 114, 202, 70, 0, 246, 179, 70, 0, 234, 206, 70, 0, 108, 190, 70, 0, 166, 162, 70, 0, 140, 180, 70, 0, 58, 221, 70, 0, 16, 215, 70, 0, 82, 206, 70, 0, 72, 202, 70, 0, 232, 207, 70, 0, 180, 188, 70, 0, 4, 202, 70, 0, 114, 209, 70, 0, 116, 224, 70, 0, 252, 221, 70, 0, 106, 216, 70, 0, 18, 221, 70, 0, 186, 224, 70, 0, 178, 225, 70, 0, 108, 226, 70, 0, 6, 206, 70, 0, 232, 206, 70, 0, 208, 211, 70, 0, 244, 206, 70, 0, 58, 211, 70, 0, 122, 216, 70, 0, 206, 149, 70, 0, 108, 136, 70, 0, 90, 161, 70, 0, 146, 176, 70, 0, 194, 147, 70, 0, 48, 123, 70, 0, 72, 141, 70, 0, 220, 114, 70, 0, 208, 196, 70, 0, 198, 204, 70, 0, 226, 176, 70, 0, 152, 190, 70, 0, 56, 212, 70, 0, 136, 221, 70, 0, 62, 203, 70, 0, 134, 217, 70, 0, 66, 225, 70, 0, 116, 225, 70, 0, 186, 225, 70, 0, 218, 225, 70, 0, 192, 225, 70, 0, 244, 225, 70, 0, 242, 225, 70, 0, 22, 226, 70, 0, 70, 226, 70, 0, 104, 226, 70, 0, 138, 226, 70, 0, 142, 226, 70, 0, 0, 104, 70, 0, 188, 113, 70, 0, 156, 119, 70, 0, 128, 120, 70, 0, 214, 135, 70, 0, 166, 147, 70, 0, 248, 149, 70, 0, 40, 141, 70, 0, 82, 137, 70, 0, 134, 141, 70, 0, 92, 157, 70, 0, 110, 162, 70, 0, 166, 161, 70, 0, 28, 159, 70, 0, 14, 160, 70, 0, 152, 175, 70, 0, 232, 170, 70, 0, 148, 168, 70, 0, 186, 164, 70, 0, 192, 178, 70, 0, 18, 182, 70, 0, 26, 186, 70, 0, 22, 189, 70, 0, 10, 192, 70, 0, 248, 193, 70, 0, 136, 200, 70, 0, 180, 197, 70, 0, 16, 206, 70, 0, 190, 209, 70, 0, 64, 213, 70, 0, 18, 217, 70 };

int32_t model_Nico_allparams_predict(const int16 *features, int32_t features_length) {

        int32_t sum = 0;

        sum += model_Nico_allparams_tree_0(features, features_length); 
    sum += model_Nico_allparams_tree_1(features, features_length); 
    sum += model_Nico_allparams_tree_2(features, features_length); 
    sum += model_Nico_allparams_tree_3(features, features_length); 
        
        return sum >> 2;  // Divide by 4 using bit shift
    }
    

#endif // MODEL_NICO_ALLPARAMS_H
