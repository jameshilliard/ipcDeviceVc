#include "./DeviceCommFuncs.h"
#include "./netLogin.h"


char cmd11000_01[]=
"1234567890123456<BasicCapability version=\"2.0\">\r\n\
<HardwareCapability>\r\n\
<HardwareVersion>0x0</HardwareVersion>\r\n\
<AlarmInPortNum>1</AlarmInPortNum>\r\n\
<AlarmOutPortNum>1</AlarmOutPortNum>\r\n\
<RS232Num>1</RS232Num>\r\n\
<RS485Num>1</RS485Num>\r\n\
<NetworkPortNum>1</NetworkPortNum>\r\n\
<USBNum>0</USBNum>\r\n\
<FlashSize>128</FlashSize>\r\n\
<RamSize>256</RamSize>\r\n\
<USBVersion>0</USBVersion>\r\n\
<SDNum>1</SDNum>\r\n\
<HardDiskNum>0</HardDiskNum>\r\n\
<SATANum>0</SATANum>\r\n\
<eSATANum>0</eSATANum>\r\n\
<miniSASNum>0</miniSASNum>\r\n\
<VideoInNum>0</VideoInNum>\r\n\
<AudioInNum>1</AudioInNum>\r\n\
<VideoOutNum>1</VideoOutNum>\r\n\
<AudioOutNum>1</AudioOutNum>\r\n\
<AudioTalkNum>1</AudioTalkNum>\r\n\
<SDSupport>1</SDSupport>\r\n\
<VideoOutSupport>1</VideoOutSupport>\r\n\
<AnalogChannelNum>1</AnalogChannelNum>\r\n\
<CVBSNumber>1</CVBSNumber>\r\n\
</HardwareCapability>\r\n\
<SoftwareCapability>\r\n\
<NewHdNo>1</NewHdNo>\r\n\
<MaxNetworkHDNum>8</MaxNetworkHDNum>\r\n\
<NasSupport>1</NasSupport>\r\n\
<NasNumber>8</NasNumber>\r\n\
<NetDiskIdentification>\r\n\
<NASIdentification>\r\n\
<NFSMountType>true</NFSMountType>\r\n\
<CIFSMountType>\r\n\
<usernameLen min=\"1\" max=\"32\"/>\r\n\
<passwordLen min=\"1\" max=\"16\"/>\r\n\
</CIFSMountType>\r\n\
</NASIdentification>\r\n\
</NetDiskIdentification>\r\n\
<ShowStringNumber>4</ShowStringNumber>\r\n\
<MotionDetectAlarmSupport>1</MotionDetectAlarmSupport>\r\n\
<HideAlarmSupport>1</HideAlarmSupport>\r\n\
<ShelterSupport>1</ShelterSupport>\r\n\
<RtspSupport>1</RtspSupport>\r\n\
<RtpoverRtspSupport>1</RtpoverRtspSupport>\r\n\
<RtspoverHttpSupport>1</RtspoverHttpSupport>\r\n\
<overHttpSupport>1</overHttpSupport>\r\n\
<NtpSupport>1</NtpSupport>\r\n\
<PtzSupport>1</PtzSupport>\r\n\
<DDNSSupport>1</DDNSSupport>\r\n\
<DDNSHostType>0,1,3,4</DDNSHostType>\r\n\
<SNMPSupport>1</SNMPSupport>\r\n\
<SNMPVersion>1,2,3</SNMPVersion>\r\n\
<UPNPSupport>1</UPNPSupport>\r\n\
<Ipv6Support>1</Ipv6Support>\r\n\
<MultipleStreamSupport>1</MultipleStreamSupport>\r\n\
<SubStreamSupport>1</SubStreamSupport>\r\n\
<EmailSupport>1</EmailSupport>\r\n\
<SADPVersion>0,1</SADPVersion>\r\n\
<MaxLoginNum>128</MaxLoginNum>\r\n\
<MaxPreviewNum>6</MaxPreviewNum>\r\n\
<MaxPlayBackNum>2</MaxPlayBackNum>\r\n\
<MaxChanLinkNum>24</MaxChanLinkNum>\r\n\
<RS232Config>1</RS232Config>\r\n\
<PPPoEConfig>1</PPPoEConfig>\r\n\
<UploadFTP>1</UploadFTP>\r\n\
<QuotaRatio>1</QuotaRatio>\r\n\
<DevModuleServerCfg>\r\n\
</DevModuleServerCfg>\r\n\
<GBT28181AccessAbilitySupport>1</GBT28181AccessAbilitySupport>\r\n\
<CameraParaDynamicAbilitySupport>1</CameraParaDynamicAbilitySupport>\r\n\
<Language>\r\n\
<supportType opt=\"1-chinese\"/>\r\n\
</Language>\r\n\
<NeedReboot>\r\n\
<ImportConfigurationFileReboot>2</ImportConfigurationFileReboot>\r\n\
<RestoreConfig>2</RestoreConfig>\r\n\
<RS232workModeChange>1</RS232workModeChange>\r\n\
<NetPortChange>1</NetPortChange>\r\n\
<DhcpEnableChange>1</DhcpEnableChange>\r\n\
<HttpPortChange>1</HttpPortChange>\r\n\
<PPPoEChange>1</PPPoEChange>\r\n\
<StandardTypeChange>1</StandardTypeChange>\r\n\
<LineCodingEnableChange>1</LineCodingEnableChange>\r\n\
<NetworkCardTypeChange>0</NetworkCardTypeChange>\r\n\
</NeedReboot>\r\n\
</SoftwareCapability>\r\n\
</BasicCapability>\r\n\
";
char cmd11000_05[]=
"1234567890123456<CAMERAPARA version=\"1.0\">\r\n\
<PowerLineFrequencyMode>\r\n\
<Range>0,1</Range>\r\n\
</PowerLineFrequencyMode>\r\n\
<WhiteBalance>\r\n\
<WhiteBalanceMode>\r\n\
<Range>0,1,2,14,4,5,6</Range>\r\n\
</WhiteBalanceMode>\r\n\
</WhiteBalance>\r\n\
<Exposure>\r\n\
</Exposure>\r\n\
<IrisMode>\r\n\
<Range>0,1</Range>\r\n\
</IrisMode>\r\n\
<BrightnessLevel>\r\n\
<Min>0</Min>\r\n\
<Max>100</Max>\r\n\
<Default>50</Default>\r\n\
</BrightnessLevel>\r\n\
<ContrastLevel>\r\n\
<Min>0</Min>\r\n\
<Max>100</Max>\r\n\
<Default>50</Default>\r\n\
</ContrastLevel>\r\n\
<SharpnessLevel>\r\n\
<Min>0</Min>\r\n\
<Max>100</Max>\r\n\
<Default>50</Default>\r\n\
</SharpnessLevel>\r\n\
<SaturationLevel>\r\n\
<Min>0</Min>\r\n\
<Max>100</Max>\r\n\
<Default>50</Default>\r\n\
</SaturationLevel>\r\n\
<WDR>\r\n\
<WDREnabled>\r\n\
<Range>0,1</Range>\r\n\
</WDREnabled>\r\n\
<WDRLevel1>\r\n\
<Min>0</Min>\r\n\
<Max>15</Max>\r\n\
</WDRLevel1>\r\n\
</WDR>\r\n\
<DayNightFilter>\r\n\
<DayNightFilterType>\r\n\
<Range>0,1,2,3,4</Range>\r\n\
</DayNightFilterType>\r\n\
<SwitchSchedule>\r\n\
<SwitchScheduleEnabled>\r\n\
<Range>0,1</Range>\r\n\
</SwitchScheduleEnabled>\r\n\
<DayToNightFilterLevel>\r\n\
<Range>0,1,2,3,4,5,6,7</Range>\r\n\
</DayToNightFilterLevel>\r\n\
<NightToDayFilterLevel>\r\n\
<Range>0,1,2,3,4,5,6,7</Range>\r\n\
</NightToDayFilterLevel>\r\n\
<DayNightFilterTime>\r\n\
<Min>5</Min>\r\n\
<Max>120</Max>\r\n\
</DayNightFilterTime>\r\n\
</SwitchSchedule>\r\n\
</DayNightFilter>\r\n\
<Backlight>\r\n\
<BacklightMode>\r\n\
<Range>0,10</Range>\r\n\
</BacklightMode>\r\n\
</Backlight>\r\n\
<Mirror>\r\n\
<Range>0,1,2,3</Range>\r\n\
</Mirror>\r\n\
<LOCALOUTPUT>\r\n\
<Range>0,1</Range>\r\n\
</LOCALOUTPUT>\r\n\
<DigitalNoiseReduction>\r\n\
<DigitalNoiseReductionEnable>\r\n\
<Range>0,1</Range>\r\n\
</DigitalNoiseReductionEnable>\r\n\
<DigitalNoiseReductionLevel>\r\n\
<Min>0</Min>\r\n\
<Max>100</Max>\r\n\
</DigitalNoiseReductionLevel>\r\n\
</DigitalNoiseReduction>\r\n\
<Dehaze>\r\n\
<Range>0,2</Range>\r\n\
</Dehaze>\r\n\
</CAMERAPARA>\r\n\
";

char cmd11000_0E[]=
"1234567890123456<VideoPicAbility version=\"2.0\">\r\n\
<channelNO>1</channelNO>\r\n\
<OSD>\r\n\
<ChannelName>\r\n\
<enabled>true</enabled>\r\n\
</ChannelName>\r\n\
<Week>\r\n\
<enabled>true</enabled>\r\n\
</Week>\r\n\
<OSDType opt=\"xxxx-xx-xxYMD,xx-xx-xxxxMDY,xx-xx-xxxxDMY,xxxxYxxMxxD,xxMxxDxxxxY,xxDxxMxxxxY,xxxx/xx/xxY/M/D,xx/xx/xxxxM/D/Y,xx/xx/xxxxD/M/Y\"/>\r\n\
<OSDAttrib opt=\"3,4\"/>\r\n\
<OSDHourType opt=\"24Hour,12Hour\"/>\r\n\
<FontSize opt=\"16*16,32*32,48*48,64*64,adaptive\"/>\r\n\
<OSDColorType opt=\"0,1\"/>\r\n\
</OSD>\r\n\
<MotionDetection>\r\n\
<regionType opt=\"grid,area\"/>\r\n\
<Grid>\r\n\
<VideoFormatP>\r\n\
<rowGranularity>18</rowGranularity>\r\n\
<columnGranularity>22</columnGranularity>\r\n\
</VideoFormatP>\r\n\
<VideoFormatN>\r\n\
<rowGranularity>15</rowGranularity>\r\n\
<columnGranularity>22</columnGranularity>\r\n\
</VideoFormatN>\r\n\
</Grid>\r\n\
<Area>\r\n\
<areaNo min=\"1\" max=\"8\"/>\r\n\
<switchDayNightSet opt=\"off,autoSwitch,scheduleSwitch\"/>\r\n\
<Off>\r\n\
<objectAreaProportion min=\"0\" max=\"100\"/>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</Off>\r\n\
<AutoSwitch>\r\n\
<supportType opt=\"day,night\"/>\r\n\
<dayObjectAreaProportion min=\"0\" max=\"100\"/>\r\n\
<daySensitivityLevel min=\"1\" max=\"100\"/>\r\n\
<nightObjectAreaProportion min=\"0\" max=\"100\"/>\r\n\
<nightSensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</AutoSwitch>\r\n\
<ScheduleSwitch>\r\n\
<supportType opt=\"day,night\"/>\r\n\
<dayObjectAreaProportion min=\"0\" max=\"100\"/>\r\n\
<daySensitivityLevel min=\"1\" max=\"100\"/>\r\n\
<nightObjectAreaProportion min=\"0\" max=\"100\"/>\r\n\
<nightSensitivityLevel min=\"1\" max=\"100\"/>\r\n\
<TimeSchedule>\r\n\
<beginTime opt=\"hour,min,sec,millisec\"/>\r\n\
<endTime opt=\"hour,min,sec,millisec\"/>\r\n\
</TimeSchedule>\r\n\
</ScheduleSwitch>\r\n\
</Area>\r\n\
<sensitivityLevel min=\"0\" max=\"100\"/>\r\n\
<NormalSensitivity>\r\n\
<level min=\"0\" max=\"5\"/>\r\n\
<step>20</step>\r\n\
<offStatus>true</offStatus>\r\n\
</NormalSensitivity>\r\n\
<alarmTime>8</alarmTime>\r\n\
<alarmHandleType opt=\"center,alarmout,picture,uploadftp\"/>\r\n\
<displayMotion opt=\"true,false\"/>\r\n\
</MotionDetection>\r\n\
<HideDetection>\r\n\
<HideAreaNum>1</HideAreaNum>\r\n\
<HideArea>\r\n\
<id>1</id>\r\n\
<PAL>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"576\"/>\r\n\
</PAL>\r\n\
<NTSC>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"480\"/>\r\n\
</NTSC>\r\n\
</HideArea>\r\n\
<sensitivity opt=\"none,low,middle,high\"/>\r\n\
<alarmTime>8</alarmTime>\r\n\
<alarmHandleType opt=\"center,alarmout,picture\"/>\r\n\
</HideDetection>\r\n\
<PrivacyMask>\r\n\
<PrivacyMaskAreaNum>4</PrivacyMaskAreaNum>\r\n\
<PrivacyMaskArea>\r\n\
<id>1</id>\r\n\
<PAL>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"576\"/>\r\n\
</PAL>\r\n\
<NTSC>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"480\"/>\r\n\
</NTSC>\r\n\
<id>2</id>\r\n\
<PAL>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"576\"/>\r\n\
</PAL>\r\n\
<NTSC>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"480\"/>\r\n\
</NTSC>\r\n\
<id>3</id>\r\n\
<PAL>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"576\"/>\r\n\
</PAL>\r\n\
<NTSC>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"480\"/>\r\n\
</NTSC>\r\n\
<id>4</id>\r\n\
<PAL>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"576\"/>\r\n\
</PAL>\r\n\
<NTSC>\r\n\
<AreaX min=\"0\" max=\"704\"/>\r\n\
<AreaY min=\"0\" max=\"480\"/>\r\n\
</NTSC>\r\n\
</PrivacyMaskArea>\r\n\
</PrivacyMask>\r\n\
</VideoPicAbility>\r\n\
";

char cmd11000_11_3C50545A[]=
"1234567890123456<PTZAbility  version=\"2.0\">\r\n\
<channelNO>1</channelNO>\r\n\
<PTZControl>\r\n\
<controlType opt=\"light,wiper,fan,heater,aux1,aux2,zoomIn,zoomOut,focusNear,focusFar,irisOpen,irisClose,ttiltUp,tiltDown,panLeft,panRight,upLeft,upRight,downLeft,downRight,panAuto,panCircle\"/>\r\n\
</PTZControl>\r\n\
<Patrol>\r\n\
<patrolNum min=\"1\" max=\"8\"/>\r\n\
<presetNum min=\"1\" max=\"32\"/>\r\n\
<dwellTime min=\"0\" max=\"120\"/>\r\n\
<speed min=\"1\" max=\"40\"/>\r\n\
</Patrol>\r\n\
<Preset>\r\n\
<presetNum min=\"1\" max=\"255\"/>\r\n\
</Preset>\r\n\
<Pattern>\r\n\
<operateType opt=\"recordStart,recordStop,run,stop,delete,deleteAll\"/>\r\n\
<patternID min=\"1\" max=\"1\"/>\r\n\
</Pattern>\r\n\
<ParkAction>\r\n\
<parkTime min=\"15\" max=\"720\"/>\r\n\
<actionType opt=\"atuoScan,patrol,preset\"/>\r\n\
<patrolID min=\"1\" max=\"8\"/>\r\n\
<presetID min=\"1\" max=\"8\"/>\r\n\
<patternID min=\"1\" max=\"4\"/>\r\n\
</ParkAction>\r\n\
<PtzBasicCfg>\r\n\
<BasicParamCfg>\r\n\
</BasicParamCfg>\r\n\
<PowerOffMemCfg>\r\n\
<resumeTimePoint opt=\"forbidden,30s,60s,300s,600s\"/>\r\n\
</PowerOffMemCfg>\r\n\
</PtzBasicCfg>\r\n\
</PTZAbility>\r\n\
";

char cmd11000_11_3C457665[]=
"1234567890123456<EventAbility version=\"2.0\">\r\n\
<channelNO>1</channelNO>\r\n\
<ExceptionAlarm>\r\n\
<exceptionType opt=\"diskFull,diskError,nicBroken,ipConflict,illAccess\"/>\r\n\
<alarmHandleType opt=\"center,alarmout,picture\"/>\r\n\
<DetailedExceptionAlarm>\r\n\
<DiskFull>\r\n\
<alarmHandleType opt=\"center,alarmout,picture\"/>\r\n\
</DiskFull>\r\n\
<DiskError>\r\n\
<alarmHandleType opt=\"center,alarmout,picture\"/>\r\n\
</DiskError>\r\n\
<NicBroken>\r\n\
<alarmHandleType opt=\"alarmout\"/>\r\n\
</NicBroken>\r\n\
<IPConflict>\r\n\
<alarmHandleType opt=\"alarmout\"/>\r\n\
</IPConflict>\r\n\
<IllAccess>\r\n\
<alarmHandleType opt=\"center,alarmout,picture\"/>\r\n\
</IllAccess>\r\n\
</DetailedExceptionAlarm>\r\n\
</ExceptionAlarm>\r\n\
<AlarmIn>\r\n\
<alarmTime>8</alarmTime>\r\n\
<alarmHandleType opt=\"center,alarmout,picture,uploadftp\"/>\r\n\
<RelatePTZ>\r\n\
<presetNo min=\"1\" max=\"8\"/>\r\n\
<CruiseNo min=\"1\" max=\"8\"/>\r\n\
<ptzTrackNo min=\"1\" max=\"1\"/>\r\n\
</RelatePTZ>\r\n\
</AlarmIn>\r\n\
<AlarmOut>\r\n\
<alarmTime>8</alarmTime>\r\n\
<pulseDuration opt=\"5,10,30,60,120,300,600,manual\"/>\r\n\
</AlarmOut>\r\n\
<VoiceDetection>\r\n\
<enable opt=\"true,false\"/>\r\n\
<Abnormal>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
<audioMode opt=\"all\"/>\r\n\
<enable  opt=\"true,false\"/>\r\n\
<threshold min=\"1\" max=\"100\"/>\r\n\
</Abnormal>\r\n\
<alarmTime>8</alarmTime>\r\n\
<alarmHandleType opt=\"center,alarmout,picture\"/>\r\n\
<audioSteepDrop>\r\n\
<enable opt=\"true,false\"/>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</audioSteepDrop>\r\n\
</VoiceDetection>\r\n\
<TraversingVirtualPlane>\r\n\
<enable opt=\"true,false\"/>\r\n\
<enableDualVca opt=\"true,false\"/>\r\n\
<alertlineNum>4</alertlineNum>\r\n\
<AlertLine>\r\n\
<id>1</id>\r\n\
<crossDirection opt=\"bothway,leftToRight,rightToLeft\"/>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</AlertLine>\r\n\
<AlertLine>\r\n\
<id>2</id>\r\n\
<crossDirection opt=\"bothway,leftToRight,rightToLeft\"/>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</AlertLine>\r\n\
<AlertLine>\r\n\
<id>3</id>\r\n\
<crossDirection opt=\"bothway,leftToRight,rightToLeft\"/>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</AlertLine>\r\n\
<AlertLine>\r\n\
<id>4</id>\r\n\
<crossDirection opt=\"bothway,leftToRight,rightToLeft\"/>\r\n\
<sensitivityLevel min=\"1\" max=\"100\"/>\r\n\
</AlertLine>\r\n\
<alarmTime>8</alarmTime>\r\n\
<alarmHandleType opt=\"center,alarmout,picture,uploadftp\"/>\r\n\
<mutexAbility opt=\"faceDetection\"/>\r\n\
</TraversingVirtualPlane>\r\n\
<FieldDetection>\r\n\
<enable opt=\"true,false\"/>\r\n\
<enableDualVca opt=\"true,false\"/>\r\n\
<intrusiongionNum>4</intrusiongionNum>\r\n\
<Intrusiongion>\r\n\
<id>1</id>\r\n\
<regionNum min=\"4\" max=\"4\"/>\r\n\
<duration min=\"0\" max=\"10\"/>\r\n\
<sensitivityLevel  min=\"1\" max=\"100\"/>\r\n\
<rate min=\"1\" max=\"100\"/>\r\n\
</Intrusiongion>\r\n\
<Intrusiongion>\r\n\
<id>2</id>\r\n\
<regionNum min=\"4\" max=\"4\"/>\r\n\
<duration min=\"0\" max=\"10\"/>\r\n\
<sensitivityLevel  min=\"1\" max=\"100\"/>\r\n\
<rate min=\"1\" max=\"100\"/>\r\n\
</Intrusiongion>\r\n\
<Intrusiongion>\r\n\
<id>3</id>\r\n\
<regionNum min=\"4\" max=\"4\"/>\r\n\
<duration min=\"0\" max=\"10\"/>\r\n\
<sensitivityLevel  min=\"1\" max=\"100\"/>\r\n\
<rate min=\"1\" max=\"100\"/>\r\n\
</Intrusiongion>\r\n\
<Intrusiongion>\r\n\
<id>4</id>\r\n\
<regionNum min=\"4\" max=\"4\"/>\r\n\
<duration min=\"0\" max=\"10\"/>\r\n\
<sensitivityLevel  min=\"1\" max=\"100\"/>\r\n\
<rate min=\"1\" max=\"100\"/>\r\n\
</Intrusiongion>\r\n\
<alarmTime>8</alarmTime>\r\n\
<alarmHandleType opt=\"center,alarmout,picture,uploadftp\"/>\r\n\
<mutexAbility opt=\"faceDetection\"/>\r\n\
</FieldDetection>\r\n\
</EventAbility>\r\n\
";
char cmd11000_08[]=
"1234567890123456<AudioVideoCompressInfo version=\"2.0\">\r\n\
<AudioCompressInfo>\r\n\
<Audio>\r\n\
<ChannelList>\r\n\
<ChannelEntry>\r\n\
<ChannelNumber>1</ChannelNumber>\r\n\
<MainAudioEncodeType>\r\n\
<Range>0,1,2,5,6,7</Range>\r\n\
<MP2L2AudioBitRate opt=\"32kbps,64kbps,128kbps\"/>\r\n\
<AACAudioBitRate opt=\"8kbps,16kbps,32kbps,64kbps\"/>\r\n\
<AACSamplingRate opt=\"16kHZ,32kHZ\"/>\r\n\
</MainAudioEncodeType>\r\n\
<SubAudioEncodeType>\r\n\
<Range>0,1,2,5,6,7</Range>\r\n\
<MP2L2AudioBitRate opt=\"32kbps,64kbps,128kbps\"/>\r\n\
<AACAudioBitRate opt=\"8kbps,16kbps,32kbps,64kbps\"/>\r\n\
<AACSamplingRate opt=\"16kHZ,32kHZ\"/>\r\n\
</SubAudioEncodeType>\r\n\
<AudioInType>\r\n\
<Range>0,1</Range>\r\n\
</AudioInType>\r\n\
<enableNoiseFilter opt=\"true,false\"/>\r\n\
<AudioInVolume>\r\n\
<Min>0</Min>\r\n\
<Max>100</Max>\r\n\
</AudioInVolume>\r\n\
</ChannelEntry>\r\n\
</ChannelList>\r\n\
</Audio>\r\n\
<VoiceTalk>\r\n\
<ChannelList>\r\n\
<ChannelEntry>\r\n\
<ChannelNumber>1</ChannelNumber>\r\n\
<VoiceTalkEncodeType>\r\n\
<Range>0,1,2,5,6,7</Range>\r\n\
</VoiceTalkEncodeType>\r\n\
<VoiceTalkInType>\r\n\
<Range>0,1</Range>\r\n\
</VoiceTalkInType>\r\n\
</ChannelEntry>\r\n\
</ChannelList>\r\n\
</VoiceTalk>\r\n\
</AudioCompressInfo>\r\n\
<VideoCompressInfo>\r\n\
<ChannelList>\r\n\
<ChannelEntry>\r\n\
<ChannelNumber>1</ChannelNumber>\r\n\
<MainChannel>\r\n\
<VideoEncodeType>\r\n\
<Range>1</Range>\r\n\
</VideoEncodeType>\r\n\
<VideoEncodeEfficiency>\r\n\
<Range>1,2</Range>\r\n\
<suportEncodeType opt=\"1\"/>\r\n\
</VideoEncodeEfficiency>\r\n\
<VideoResolutionList>\r\n\
<VideoResolutionEntry>\r\n\
<Index>19</Index>\r\n\
<Name>720P</Name>\r\n\
<Resolution>1280*720</Resolution>\r\n\
<VideoFrameRate>0,1,2,3,4,5,6,7,8,9,10,11,14,12,15,13,16,17</VideoFrameRate>\r\n\
<VideoBitrate>\r\n\
<Min>32</Min>\r\n\
<Max>12288</Max>\r\n\
</VideoBitrate>\r\n\
</VideoResolutionEntry>\r\n\
<VideoResolutionEntry>\r\n\
<Index>20</Index>\r\n\
<Name>XVGA</Name>\r\n\
<Resolution>1280*960</Resolution>\r\n\
<VideoFrameRate>0,1,2,3,4,5,6,7,8,9,10,11,14,12,15,13,16,17</VideoFrameRate>\r\n\
<VideoBitrate>\r\n\
<Min>32</Min>\r\n\
<Max>12288</Max>\r\n\
</VideoBitrate>\r\n\
</VideoResolutionEntry>\r\n\
<DynamicAbility>\r\n\
<dynamicAbilityLinkTo opt=\"captureMode\"/>\r\n\
</DynamicAbility>\r\n\
</VideoResolutionList>\r\n\
<IntervalBPFrame>\r\n\
<Range>2</Range>\r\n\
</IntervalBPFrame>\r\n\
<EFrame>0</EFrame>\r\n\
<SVCFunEnable  opt=\"true,false\"/>\r\n\
<SVCSupportEncodeType opt=\"1\"/>\r\n\
<intervalIFrame min=\"1\" max=\"400\"/>\r\n\
<StreamSmooth>\r\n\
<level min=\"1\" max=\"100\"/>\r\n\
<supportEncodeType opt=\"1\"/>\r\n\
<supportRateType opt=\"constant\"/>\r\n\
</StreamSmooth>\r\n\
</MainChannel>\r\n\
<SubChannelList>\r\n\
<SubChannelEntry>\r\n\
<index>1</index>\r\n\
<VideoEncodeType>\r\n\
<Range>1,7</Range>\r\n\
</VideoEncodeType>\r\n\
<VideoEncodeEfficiency>\r\n\
<Range>1,2</Range>\r\n\
<suportEncodeType opt=\"1\"/>\r\n\
</VideoEncodeEfficiency>\r\n\
<VideoResolutionList>\r\n\
<VideoResolutionEntry>\r\n\
<Index>6</Index>\r\n\
<Name>QVGA</Name>\r\n\
<Resolution>320*240</Resolution>\r\n\
<VideoFrameRate>0,1,2,3,4,5,6,7,8,9,10,11,14,12,15,13,16,17</VideoFrameRate>\r\n\
<VideoBitrate>\r\n\
<Min>32</Min>\r\n\
<Max>8192</Max>\r\n\
</VideoBitrate>\r\n\
</VideoResolutionEntry>\r\n\
<VideoResolutionEntry>\r\n\
<Index>1</Index>\r\n\
<Name>CIF</Name>\r\n\
<Resolution>352*288</Resolution>\r\n\
<VideoFrameRate>0,1,2,3,4,5,6,7,8,9,10,11,14,12,15,13,16,17</VideoFrameRate>\r\n\
<VideoBitrate>\r\n\
<Min>32</Min>\r\n\
<Max>8192</Max>\r\n\
</VideoBitrate>\r\n\
</VideoResolutionEntry>\r\n\
<VideoResolutionEntry>\r\n\
<Index>3</Index>\r\n\
<Name>4CIF</Name>\r\n\
<Resolution>704*576</Resolution>\r\n\
<VideoFrameRate>0,1,2,3,4,5,6,7,8,9,10,11,14,12,15,13,16,17</VideoFrameRate>\r\n\
<VideoBitrate>\r\n\
<Min>32</Min>\r\n\
<Max>8192</Max>\r\n\
</VideoBitrate>\r\n\
</VideoResolutionEntry>\r\n\
<DynamicAbility>\r\n\
<dynamicAbilityLinkTo opt=\"captureMode\"/>\r\n\
</DynamicAbility>\r\n\
</VideoResolutionList>\r\n\
<IntervalBPFrame>\r\n\
<Range>2</Range>\r\n\
</IntervalBPFrame>\r\n\
<EFrame>0</EFrame>\r\n\
<SVCFunEnable  opt=\"true,false\"/>\r\n\
<SVCSupportEncodeType opt=\"1\"/>\r\n\
<intervalIFrame min=\"1\" max=\"400\"/>\r\n\
<StreamSmooth>\r\n\
<level min=\"1\" max=\"100\"/>\r\n\
<supportEncodeType opt=\"1\"/>\r\n\
<supportRateType opt=\"constant\"/>\r\n\
</StreamSmooth>\r\n\
</SubChannelEntry>\r\n\
</SubChannelList>\r\n\
</ChannelEntry>\r\n\
</ChannelList>\r\n\
</VideoCompressInfo>\r\n\
<StreamAttachInfo>\r\n\
<streamWithVca>true</streamWithVca>\r\n\
</StreamAttachInfo>\r\n\
</AudioVideoCompressInfo>\r\n\
";


#ifndef SUPPORT_IPV6
int getLoginRetval(int userID,NET_LOGIN_REQ loginData,NET_LOGIN_RET* loginRet)
#else
int getLoginRetval(int userID,NET_LOGIN_REQ_V6 *pLoginData,NET_LOGIN_RET* loginRet)
#endif
{
	char buf1[80];
	UINT8 devModel[16];
	IMPORT int getIpCameraCount();
	
	if(loginRet == NULL)
	{
		return ERROR;
	}

	loginRet->length = htonl(sizeof(NET_LOGIN_RET));
	loginRet->retVal = htonl(NETRET_QUALIFIED);
	loginRet->userID = htonl(userID);
	#if 0 //zss++
	makeProductModel(&bootParms,(char *)devModel);
	makeSerialNo(&bootParms,buf1);
	memcpy(loginRet->serialno, buf1, SERIALNO_LEN);
    #ifndef SUPPORT_IPV6
	loginRet->devSdkVer = htonl(loginData.version);
	loginRet->devType =   getNetRetDveType(loginData.version);
    #else
	loginRet->devSdkVer = htonl(pLoginData->version);
	loginRet->devType =   getNetRetDveType(pLoginData->version);
    #endif
	loginRet->channelNums = devHardInfo.encodeChans;
	loginRet->firstChanNo = FIRST_CHAN_NO;
	loginRet->alarmInNums = devHardInfo.alarmInNums;
	loginRet->alarmOutNums = devHardInfo.alarmOutNums;
	loginRet->hdiskNums = getHdiskNums();
#ifdef RTSP
	loginRet->supportProtocols = 0xf0;
    loginRet->supportProtocols = 0x0f;
#else
	loginRet->supportProtocols = 0x0f;
#endif
#if !defined(DM6467) && !defined(HI3515)
	loginRet->audioChanNums = 2;
#else
	loginRet->audioChanNums = 1;
#endif
	loginRet->maxIpcChanNums = getMaxIPCCount();
#ifdef DVS65
	loginRet->support = isDualNetPort() ? 0x8 : 0;
#endif
#ifdef	SUPPORT_SNMP
	loginRet->support1 |= 0x1;
#endif
	#endif

	memcpy(loginRet->serialno, SerialNo, strlen(SerialNo));
	loginRet->devSdkVer = htonl(loginData.version);
	loginRet->devType =   DevType;
	loginRet->channelNums = ChannelNums;
	loginRet->firstChanNo = FirstChanNo;
	loginRet->alarmInNums = AlarmInNums;
	loginRet->alarmOutNums = AlarmOutNums;
	loginRet->hdiskNums = HdiskNums;
	loginRet->supportProtocols = SupportProtocols;
	loginRet->audioChanNums = AudioChanNums;
	loginRet->maxIpcChanNums = MaxIpcChanNums;
	loginRet->support = Support0;
	loginRet->support1 = 0x0;

	return OK;
}




#ifndef SUPPORT_IPV6
/*
 * =====================================================================
 * Function: netClientLogin
 * Description:user login 
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientLogin(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	struct in_addr clientIpAddr;
	struct sockaddr_in peer;
	NET_LOGIN_REQ loginData;
	NET_LOGIN_RET loginRet;
	int userID;
	UINT32 clientVersion;
	STATUS retVal;
	NETCMD_HEADER netCmdHeader;

   	bzero((char *)&peer,sizeof(struct sockaddr_in));
   	bzero((char *)&clientIpAddr,sizeof(struct in_addr));
   	bzero((char *)&loginData,sizeof(NET_LOGIN_REQ));
   	bzero((char *)&loginRet, sizeof(NET_LOGIN_RET));
       
	//zss+get_peer_name(connfd,&peer);

	memcpy((char *)&loginData, recvbuff, sizeof(NET_LOGIN_REQ)); 
	convertNetLoginReqByteOrder(&loginData);
	
	loginRet.length = htonl(sizeof(NET_LOGIN_RET));


	/* check version */
	if ( loginData.ifVer != NEW_NETSDK_INTERFACE )
   	{
		NET_ERR(("Invalid ifVer 0x%x\n", loginData.ifVer));
		loginRet.retVal = htonl(NETRET_VER_DISMATCH);
	}
	else
	{	/* try to login */
		NET_INFO(("netClientLogin: sdkVersion = 0x%x\n", loginData.version));
		clientVersion = loginData.version;
		if ( loginData.version > CURRENT_NETSDK_VERSION )
		{
			loginData.version = CURRENT_NETSDK_VERSION;
		}

		/* Feb28,2008 - xiemq add for DS9000 login */
		/* Aug03,2009 - menghong modify */
		if ( loginData.version >= NETSDK_VERSION3_0 )
		{
			NET_INFO(("DS9000 login.\n"));
			retVal = challenge_login(connfd, &loginData, &userID, &peer);
			if(retVal != OK)
			{
				NET_INFO(("DS9000 login failed\n"));
				loginRet.retVal = htonl(retVal);
				loginRet.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
			}
			else
			{
				NET_INFO(("DS9000 login success\n"));
				getLoginRetval(userID,loginData, &loginRet);
			}
		}
		else
		{	
			NET_INFO(("no DS9000 login.\n"));
			#if 0
			clientIpAddr.s_addr = loginData.clientIp;	
			retVal = userLogin((char *)loginData.username, (char *)loginData.password, &clientIpAddr, 
					&peer.sin_addr, (char *)loginData.clientMac, &userID, loginData.version);

			if ( retVal == OK ) 
			{
				NET_INFO(("login successful, userID = 0x%x\n", userID));
				if ( GET_NETSDK_BUILDDATE(clientVersion) >= GET_NETSDK_BUILDDATE(NETSDK_VERSION2_1) ) 
				{
					NET_INFO(("New SDK: need relogin.\n"));
					loginRet.retVal = ntohl(NETRET_NEED_RELOGIN);
					userLogout(FALSE, userID, &clientIpAddr, &peer.sin_addr, (char *)loginData.clientMac);
				}
				else
				{
					getLoginRetval(userID,loginData, &loginRet);
				}
			}
			else 
			{
				NET_ERR(("userLogin failed: retval = 0x%x\n", retVal));
				loginRet.retVal = htonl(retVal);
				loginRet.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
			}
			#endif
		}
	}

	
	loginRet.checkSum = checkByteSum((char *)&(loginRet.retVal), sizeof(NET_LOGIN_RET)-8);
	return connfd.sendBytes((const char *)&loginRet, sizeof(NET_LOGIN_RET),0);
	//zss++return writen(connfd, (char *)&loginRet, sizeof(NET_LOGIN_RET));
}
#else

/*
 * =====================================================================
 * Function: netClientLogin
 * Description:user login 
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientLogin(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
    U_IN_ADDR clientIp;
    U_IN_ADDR peerIp;
    NET_LOGIN_REQ_V6 *pLoginData6;
    UINT8	username[NAME_LEN];
    UINT8	password[PASSWD_LEN];
    
    NET_LOGIN_RET loginRet;
    int userID;
    UINT32 clientVersion;
    STATUS retVal;

    bzero(&clientIp,sizeof(U_IN_ADDR));
    bzero(&peerIp,sizeof(U_IN_ADDR));
    bzero(&loginRet, sizeof(NET_LOGIN_RET));
    
    get_peer_addr(connfd, &peerIp);
    pLoginData6 = (NET_LOGIN_REQ_V6 *)recvbuff;
    convertNetLoginReqByteOrder(pLoginData6);
    if(pLoginData6->ipVer)
    {
        memcpy(username, (recvbuff+sizeof(NET_LOGIN_REQ_V6)), sizeof(username));
        memcpy(password, (recvbuff+sizeof(NET_LOGIN_REQ_V6))+sizeof(username), sizeof(password));
        NET_INFO(("ipv6 login.name %s, password %s\n", username, password));
   }
    else
    {
        memcpy(username, (recvbuff+sizeof(NET_LOGIN_REQ)), sizeof(username));
        memcpy(password, (recvbuff+sizeof(NET_LOGIN_REQ))+sizeof(username), sizeof(password));
        NET_INFO(("ipv4 login.name %s, password %s\n", username, password));
    }
    
    loginRet.length = htonl(sizeof(NET_LOGIN_RET));

    /* check version */
    if ( pLoginData6->ifVer != NEW_NETSDK_INTERFACE )
    {
        NET_ERR(("Invalid ifVer 0x%x\n", pLoginData6->ifVer));
        loginRet.retVal = htonl(NETRET_VER_DISMATCH);
    }
    else
    {   /* try to login */
        NET_INFO(("netClientLogin: sdkVersion = 0x%x\n", pLoginData6->version));
        clientVersion = pLoginData6->version;
        if ( pLoginData6->version > CURRENT_NETSDK_VERSION )
        {
            pLoginData6->version = CURRENT_NETSDK_VERSION;
        }

        /* Feb28,2008 - xiemq add for DS9000 login */
        /* Aug03,2009 - menghong modify */
        if ( pLoginData6->version >= NETSDK_VERSION3_0 )
        {
            NET_INFO(("DS9000 login.\n"));
            retVal = challenge_login(connfd, pLoginData6, &userID, &peerIp);
            if(retVal != OK)
            {
                NET_INFO(("DS9000 login failed\n"));
                loginRet.retVal = htonl(retVal);
                loginRet.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
            }
            else
            {
                getLoginRetval(userID,pLoginData6, &loginRet);
            }
        }
        else
        {
            clientIp.v4.s_addr = pLoginData6->clientIp;
            if(pLoginData6->ipVer)
            {
                memcpy(&clientIp.v6, &pLoginData6->clientIp6, sizeof(struct in6_addr));
            }
            retVal = userLogin((char *)username, (char *)password, &clientIp, 
                    &peerIp, (char *)pLoginData6->clientMac, &userID, pLoginData6->version);

            if ( retVal == OK ) 
            {
                NET_INFO(("login successful, userID = 0x%x\n", userID));
                if ( GET_NETSDK_BUILDDATE(clientVersion) >= GET_NETSDK_BUILDDATE(NETSDK_VERSION2_1) ) 
                {
                    NET_INFO(("New SDK: need relogin.\n"));
                    loginRet.retVal = ntohl(NETRET_NEED_RELOGIN);
                    userLogout(FALSE, userID, &clientIp, &peerIp, (char *)pLoginData6->clientMac);
                }
                else
                {
                    getLoginRetval(userID,pLoginData6, &loginRet);
                }
            }
            else 
            {
                NET_ERR(("userLogin failed: retval = 0x%x\n", retVal));
                loginRet.retVal = htonl(retVal);
                loginRet.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
            }
        }
    }
    loginRet.checkSum = checkByteSum((char *)&(loginRet.retVal), sizeof(NET_LOGIN_RET)-8);
    return writen(connfd, (char *)&loginRet, sizeof(NET_LOGIN_RET));
}

#endif

#ifndef SUPPORT_IPV6
/*
 * =====================================================================
 * Function: netClientLogout
 * Description:user logout
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientLogout(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_HEADER  netCmdHeader;
	UINT32 retVal;
	struct in_addr clientIpAddr;
    struct sockaddr_in peer;

    bzero((char *)&clientIpAddr,sizeof(struct in_addr));
    bzero((char *)&peer, sizeof(struct sockaddr_in));  
    
	memcpy(&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	convertNetCmdHeaderByteOrder(&netCmdHeader);

    //zss++get_peer_name(connfd,&peer);    
	clientIpAddr.s_addr = netCmdHeader.clientIp;
	/* logout */
	//if ( userLogout(FALSE, netCmdHeader.userID, &clientIpAddr, &peer.sin_addr, (char *)netCmdHeader.clientMac) == OK )
	if(1)
	{
		retVal = NETRET_QUALIFIED;
	}
	else
	{
		retVal = NETRET_NO_USERID;
	}
	NETRET_HEADER  netRetHeader;
	int sendlen;

	sendlen = sizeof(NETRET_HEADER);
	bzero((char *)&netRetHeader, sendlen);
	netRetHeader.length = htonl(sendlen);
	netRetHeader.retVal = htonl(retVal);
	netRetHeader.checkSum = htonl(checkByteSum((char *)&(netRetHeader.retVal), sendlen-8));
	//zss++return writen(connfd, (char *)&netRetHeader, sendlen);
	return connfd.sendBytes((char *)&netRetHeader, sendlen,0);
	//zss++return sendNetRetval(connfd, retVal);
}
#else
/*
 * =====================================================================
 * Function: netClientLogout
 * Description:user logout
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientLogout(int connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
    NETCMD_HEADER_V6 *pNetCmdHeader6;
    UINT32 retVal;
    U_IN_ADDR clientIpAddr;
    U_IN_ADDR peer;

    bzero(&clientIpAddr,sizeof(U_IN_ADDR));
    bzero(&peer, sizeof(U_IN_ADDR));  

    pNetCmdHeader6 = (NETCMD_HEADER_V6 *)recvbuff;
    convertNetCmdHeaderByteOrderV6(pNetCmdHeader6);

    get_peer_addr(connfd,&peer);    
    clientIpAddr.v4.s_addr = pNetCmdHeader6->clientIp;
    if(pNetCmdHeader6->ipVer)
    {
        memcpy(&clientIpAddr.v6, &pNetCmdHeader6->clientIp6, sizeof(struct in6_addr));
    }
    /* logout */
    if(userLogout(FALSE, pNetCmdHeader6->userID, &clientIpAddr, &peer, (char *)pNetCmdHeader6->clientMac) == OK )
    {
        retVal = NETRET_QUALIFIED;
    }
    else
    {
        retVal = NETRET_NO_USERID;
    }

    return sendNetRetval(connfd, retVal);
}

#endif
#if 0
#ifndef SUPPORT_IPV6
/*
 * =====================================================================
 * Function: netClientReLogin
 * Description:user login again 
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientReLogin(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NET_LOGIN_REQ loginData;
	NET_LOGIN_RET loginRet;
	struct in_addr clientIpAddr;
    struct sockaddr_in peer;
	int userID;
	STATUS retVal;
	NETCMD_HEADER netCmdHeader;
	
	unsigned char PrivateKey[16] = {0x6a,0x68,0xa3,0x61,0xbf,0x6e,0xb5,0x67,0xcd,0x7a,0xfe,0x68,0xca,0x6f,0xde,0x75};
	unsigned char desIn[16];

	bzero((char *)&peer,sizeof(struct sockaddr_in));
	bzero((char *)&clientIpAddr,sizeof(struct in_addr));
	bzero((char *)&loginData,sizeof(NET_LOGIN_REQ));
	bzero((char *)&loginRet, sizeof(NET_LOGIN_RET));

	get_peer_name(connfd,&peer);

    memcpy((char *)&loginData, recvbuff, sizeof(NET_LOGIN_REQ));
	convertNetLoginReqByteOrder(&loginData);

	loginRet.length = htonl(sizeof(NET_LOGIN_RET));
	if ( loginData.ifVer != NEW_NETSDK_INTERFACE )
   	{
		NET_ERR(("Invalid ifVer 0x%x\n", loginData.ifVer));
		loginRet.retVal = htonl(NETRET_VER_DISMATCH);
	}
	else
   	{	
		NET_INFO(("netClientLogin: sdkVersion = 0x%x\n", loginData.version));
		if ( loginData.version>CURRENT_NETSDK_VERSION )
	   	{
			loginData.version = CURRENT_NETSDK_VERSION;
		}

		/*username encrypt*/
		bzero((char *)desIn, 16);
		memcpy(desIn, loginData.username, 16);
		bzero((char *)loginData.username, 32);
		des2key(PrivateKey, 1);
		D2des(desIn, loginData.username);

		/*password encrypt*/
		bzero((char *)desIn, 16);
		memcpy(desIn, loginData.password, 16);
		bzero((char *)loginData.password, 16);
		des2key(PrivateKey, 1);
		D2des(desIn, loginData.password);

		/* try to login */
		clientIpAddr.s_addr = loginData.clientIp;	
		retVal = userLogin((char *)loginData.username, (char *)loginData.password, &clientIpAddr,
			&peer.sin_addr, (char *)loginData.clientMac, &userID, loginData.version|RELOGIN_FLAG);
		if(retVal == OK) 
		{
			getLoginRetval(userID,loginData, &loginRet);
		}
		else
		{
			NET_ERR(("userLogin failed: retval = 0x%x\n", retVal));
			loginRet.retVal = htonl(retVal);
			loginRet.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
		}
	}
    
	loginRet.checkSum = checkByteSum((char *)&(loginRet.retVal), sizeof(NET_LOGIN_RET)-8);

	return writen(connfd, (char *)&loginRet, sizeof(NET_LOGIN_RET));
}
#else
/*
 * =====================================================================
 * Function: netClientReLogin
 * Description:user login again 
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientReLogin(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
    NET_LOGIN_REQ_V6 *pLoginData6;
    UINT8	username[NAME_LEN];
    UINT8	password[PASSWD_LEN];
    NET_LOGIN_RET loginRet;
    U_IN_ADDR clientIp;
    U_IN_ADDR peer;
    int userID;
    STATUS retVal;
    
    unsigned char PrivateKey[16] = {0x6a,0x68,0xa3,0x61,0xbf,0x6e,0xb5,0x67,0xcd,0x7a,0xfe,0x68,0xca,0x6f,0xde,0x75};
    unsigned char desIn[16];

    bzero(&peer,sizeof(U_IN_ADDR));
    bzero(&clientIp,sizeof(U_IN_ADDR));
    bzero(&loginRet, sizeof(NET_LOGIN_RET));

    get_peer_addr(connfd,&peer);

    pLoginData6 = (NET_LOGIN_REQ_V6 *)recvbuff;
    convertNetLoginReqByteOrder(pLoginData6);
    if(pLoginData6->ipVer)
    {
        memcpy(username, (recvbuff+sizeof(NET_LOGIN_REQ_V6)), sizeof(username));
        memcpy(password, (recvbuff+sizeof(NET_LOGIN_REQ_V6))+sizeof(username), sizeof(password));
   }
    else
    {
        memcpy(username, (recvbuff+sizeof(NET_LOGIN_REQ)), sizeof(username));
        memcpy(password, (recvbuff+sizeof(NET_LOGIN_REQ))+sizeof(username), sizeof(password));
    }

    loginRet.length = htonl(sizeof(NET_LOGIN_RET));
    if (pLoginData6->ifVer != NEW_NETSDK_INTERFACE)
    {
        NET_ERR(("Invalid ifVer 0x%x\n", pLoginData6->ifVer));
        loginRet.retVal = htonl(NETRET_VER_DISMATCH);
    }
    else
    {   
        NET_INFO(("netClientLogin: sdkVersion = 0x%x\n", pLoginData6->version));
        if ( pLoginData6->version>CURRENT_NETSDK_VERSION )
        {
            pLoginData6->version = CURRENT_NETSDK_VERSION;
        }

        /*username encrypt*/
        bzero(desIn, 16);
        memcpy(desIn, username, 16);
        bzero(username, 32);
        des2key(PrivateKey, 1);
        D2des(desIn, username);

        /*password encrypt*/
        bzero(desIn, 16);
        memcpy(desIn, password, 16);
        bzero(password, 16);
        des2key(PrivateKey, 1);
        D2des(desIn, password);

        /* try to login */
        clientIp.v4.s_addr = pLoginData6->clientIp;   
        if(pLoginData6->ipVer)
        {
            memcpy(&clientIp.v6, &pLoginData6->clientIp6, sizeof(struct in6_addr));
        }
        retVal = userLogin((char *)username, (char *)password, &clientIp,
            &peer, (char *)pLoginData6->clientMac, &userID, pLoginData6->version|RELOGIN_FLAG);
        if(retVal == OK) 
        {
            getLoginRetval(userID, pLoginData6, &loginRet);
        }
        else
        {
            NET_ERR(("userLogin failed: retval = 0x%x\n", retVal));
            loginRet.retVal = htonl(retVal);
            loginRet.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
        }
    }
    
    loginRet.checkSum = checkByteSum((char *)&(loginRet.retVal), sizeof(NET_LOGIN_RET)-8);

    return writen(connfd, (char *)&loginRet, sizeof(NET_LOGIN_RET));
}

#endif

#endif

#ifndef SUPPORT_IPV6
/*
 * =====================================================================
 * Function: netClientUserExchange
 * Description:user exchange - keep alive
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientUserExchange(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	
	NETCMD_HEADER  netCmdHeader;
	struct in_addr clientIpAddr;
    	struct sockaddr_in peer;
	UINT32 retVal;

    bzero((char *)&peer,sizeof(struct sockaddr_in));
    
	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	convertNetCmdHeaderByteOrder(&netCmdHeader);

    //zss++get_peer_name(connfd.sockfd(),&peer);
	clientIpAddr.s_addr = netCmdHeader.clientIp;
    
	//zss++if (userKeepAlive(netCmdHeader.userID, &clientIpAddr, &peer.sin_addr, (char *)netCmdHeader.clientMac) == OK )
	if(1)
	{
		retVal = NETRET_QUALIFIED;
	}
	else
	{
		retVal = NETRET_NO_USERID;
	}

	NETRET_HEADER  netRetHeader;
	int sendlen;

	sendlen = sizeof(NETRET_HEADER);
	bzero((char *)&netRetHeader, sendlen);
	netRetHeader.length = htonl(sendlen);
	netRetHeader.retVal = htonl(retVal);
	netRetHeader.checkSum = htonl(checkByteSum((char *)&(netRetHeader.retVal), sendlen-8));
	//zss++return writen(connfd, (char *)&netRetHeader, sendlen);
	return connfd.sendBytes((char *)&netRetHeader, sendlen,0);

}
#else
/*
 * =====================================================================
 * Function: netClientUserExchange
 * Description:user exchange - keep alive
 * Input:  connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *======================================================================
 */
STATUS netClientUserExchange(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
    NETCMD_HEADER_V6 *pNetCmdHeader6;
    U_IN_ADDR clientIpAddr;
    U_IN_ADDR peer;
    UINT32 retVal;

    pNetCmdHeader6 = (NETCMD_HEADER_V6 *)recvbuff;
    convertNetCmdHeaderByteOrderV6(pNetCmdHeader6);

    get_peer_addr(connfd,&peer);
    clientIpAddr.v4.s_addr = pNetCmdHeader6->clientIp;
    if(pNetCmdHeader6->ipVer)
    {
        memcpy(&clientIpAddr.v6, &pNetCmdHeader6->clientIp6, sizeof(struct in6_addr));
    }
    
    if (userKeepAlive(pNetCmdHeader6->userID, &clientIpAddr, &peer, (char *)pNetCmdHeader6->clientMac) == OK )
    {
        retVal = NETRET_QUALIFIED;
    }
    else
    {
        retVal = NETRET_NO_USERID;
    }
    
    return sendNetRetval(connfd, retVal);
}

#endif


#ifdef RTSP
/******************************************************************************
 * Function: netClientSetRtspCfg
 * Description: net client set rtsp config param
 * Input:
 *		   connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *****************************************************************************/
#if 0
STATUS netClientSetRtspCfg(int connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	struct{
		NETCMD_HEADER header;
		NETPARAM_RTSP_CFG rtspCfg;
	}netCmdRtspCfg;
	UINT32 retVal;
	NETWORK *pNetCfg;

	memcpy((char *)&netCmdRtspCfg, recvbuff, sizeof(netCmdRtspCfg));
	retVal = verifyNetClientOperation(&(netCmdRtspCfg.header), pClientSockAddr, REMOTESETPARAMETER);

	if(retVal == NETRET_QUALIFIED)
	{
		if (ntohl(netCmdRtspCfg.rtspCfg.length) != sizeof(NETPARAM_RTSP_CFG))	/* check length */
		{
			NET_ERR(("Error length : %d, %d\n", ntohl(netCmdRtspCfg.rtspCfg.length), sizeof(NETPARAM_RTSP_CFG)));
			retVal = NETRET_ERROR_DATA;
		}
		else
		{
			pNetCfg = &(pDevCfgParam->networkPara);
			if (netCmdRtspCfg.rtspCfg.rtspPort == 0
				|| (ntohs(netCmdRtspCfg.rtspCfg.rtspPort) == pNetCfg->etherNet[0].ipPortNo)
				|| (ntohs(netCmdRtspCfg.rtspCfg.rtspPort) == pNetCfg->httpPortNo))
			{
				NET_ERR(("Invalid rtsp port.\n"));
				retVal = NETRET_ERROR_DATA;
				goto errExit;
			}

			writeOperationLogEntry(netCmdRtspCfg.header.userID, MINOR_REMOTE_CFG_PARM, PARA_NETWORK);

			/* copy to pDevCfgParam */
			pthreadMutexLock(&globalMSem, WAIT_FOREVER);
			pDevCfgParam->rtspPort = ntohs(netCmdRtspCfg.rtspCfg.rtspPort);
			if (writeDevParam(pDevCfgParam) != OK)
			{
				retVal = NETRET_DVR_OPER_FAILED;
			}
			pthreadMutexUnlock(&globalMSem);
		}
	}
errExit:
    #ifdef NET_PUSH_SDK
    return net_write_resp(connfd, NULL, sizeof(NETRET_HEADER), retVal, recvbuff);
    #else   
	return sendNetRetval(connfd, retVal);
    #endif
}

/******************************************************************************
 * Function: netClientGetRtspCfg
 * Description: net client get rtsp config param
 * Input:
 *		   connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *****************************************************************************/
STATUS netClientGetRtspCfg(int connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_HEADER  netCmdHeader;
	struct{
		NETRET_HEADER header;
		NETPARAM_RTSP_CFG rtspCfg;
	}netCmdRtspCfg;
	UINT32 retVal;
	int sendlen, i;

	sendlen = sizeof(netCmdRtspCfg);
	bzero((char *)&netCmdRtspCfg, sendlen);
	netCmdRtspCfg.header.length = htonl(sendlen);

	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	retVal = verifyNetClientOperation(&netCmdHeader, pClientSockAddr, REMOTESHOWPARAMETER);
	if(retVal == NETRET_QUALIFIED)
	{
		writeOperationLogEntry(netCmdHeader.userID, MINOR_REMOTE_GET_PARM, PARA_NETWORK);
		netCmdRtspCfg.rtspCfg.length = htonl(sizeof(NETPARAM_RTSP_CFG));
		netCmdRtspCfg.rtspCfg.rtspPort = htons(pDevCfgParam->rtspPort);
	}

	netCmdRtspCfg.header.retVal = htonl(retVal);
	netCmdRtspCfg.header.checkSum = htonl(checkByteSum((char *)&(netCmdRtspCfg.header.retVal), sendlen - 8));
    #ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netCmdRtspCfg, sendlen, retVal, recvbuff);
    #else
    return writen(connfd, (char *)&netCmdRtspCfg, sendlen);
    #endif
}
#endif

/*********************************************************************
 * Function: netClientGetDeviceCfg
 * Description:get device parameter
 * Input:
 *		  connfd - socket connfd 
 *        recvbuff - recevie data buff
 *        pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *********************************************************************/
STATUS netClientGetDeviceCfg(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_HEADER  netCmdHeader;
	struct{
		NETRET_HEADER header;
		NETPARAM_DEVICE_CFG deviceCfg;
	}netRetDeviceCfg;
	UINT32 retVal;
	int sendlen;
	char buf1[80];
	//UINT8 devModel[64];

	sendlen = sizeof(netRetDeviceCfg);
	bzero((char *)&netRetDeviceCfg, sendlen);
	netRetDeviceCfg.header.length = htonl(sendlen);

	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	//zss++retVal = verifyNetClientOperation(&netCmdHeader, pClientSockAddr, REMOTESHOWPARAMETER);
	retVal = NETRET_QUALIFIED;
	if(retVal == NETRET_QUALIFIED)
	{
		//zss++writeOperationLogEntry(netCmdHeader.userID, MINOR_REMOTE_GET_PARM, PARA_DEVICE);

		netRetDeviceCfg.deviceCfg.length = htonl(sizeof(NETPARAM_DEVICE_CFG));
		//memcpy(netRetDeviceCfg.deviceCfg.DVRName,DevName, NAME_LEN);
		netRetDeviceCfg.deviceCfg.DVRName[0]=0x5a;
		netRetDeviceCfg.deviceCfg.DVRName[1]=0x59;
		netRetDeviceCfg.deviceCfg.deviceID = htonl(0x00000058);
		netRetDeviceCfg.deviceCfg.recycleRecord = htonl((UINT32)(1));
		//makeProductModel(&bootParms,(char *)devModel);
		//makeSerialNo(&bootParms,buf1);
		memcpy(netRetDeviceCfg.deviceCfg.serialno, SerialNo, SERIALNO_LEN);
        netRetDeviceCfg.deviceCfg.softwareVersion = htonl(0x05020000);
        netRetDeviceCfg.deviceCfg.softwareBuildDate = htonl(0x000E0A1C);
        netRetDeviceCfg.deviceCfg.dspSoftwareVersion = htonl(0x00050000);
        netRetDeviceCfg.deviceCfg.dspSoftwareBuildDate = htonl(0x000E0814);
#if defined(DM6467) || defined(HI3515)
		netRetDeviceCfg.deviceCfg.panelVersion = htonl(devHardInfo.panelVersion);
#else
		netRetDeviceCfg.deviceCfg.panelVersion = htonl((UINT32)0);
#endif
		netRetDeviceCfg.deviceCfg.hardwareVersion = htonl(0);
		netRetDeviceCfg.deviceCfg.alarmInNums = (UINT8)1;
		netRetDeviceCfg.deviceCfg.alarmOutNums = (UINT8)1;
//		#ifdef HI3515
		netRetDeviceCfg.deviceCfg.rs232Nums = 1;
		netRetDeviceCfg.deviceCfg.rs485Nums = 1;
//		#else
//		netRetDeviceCfg.deviceCfg.rs232Nums = 1;
//		netRetDeviceCfg.deviceCfg.rs485Nums = 1;
//		#endif
		netRetDeviceCfg.deviceCfg.netIfNums = 1;
		netRetDeviceCfg.deviceCfg.hdiskCtrlNums = (UINT8)0;
		netRetDeviceCfg.deviceCfg.hdiskNums = 0;
		netRetDeviceCfg.deviceCfg.devType = 0x0;
		netRetDeviceCfg.deviceCfg.channelNums = 1;
		netRetDeviceCfg.deviceCfg.firstChanNo = 1;
		netRetDeviceCfg.deviceCfg.decodeChans = (UINT8)0;
		netRetDeviceCfg.deviceCfg.vgaNums = 0;
		netRetDeviceCfg.deviceCfg.usbNums = 0;
		netRetDeviceCfg.deviceCfg.auxOutNum = 0;
		netRetDeviceCfg.deviceCfg.audioNum = 0;
		netRetDeviceCfg.deviceCfg.ipChanNum = 0;
		NET_INFO(("alarmIn = %d, alarmOut = %d, hdiskCtrl = %d, hdisk = %d, enc = %d, dec = %d\n",
			netRetDeviceCfg.deviceCfg.alarmInNums, netRetDeviceCfg.deviceCfg.alarmOutNums,
			netRetDeviceCfg.deviceCfg.hdiskCtrlNums, netRetDeviceCfg.deviceCfg.hdiskNums,
			netRetDeviceCfg.deviceCfg.channelNums, netRetDeviceCfg.deviceCfg.decodeChans));
	}

	netRetDeviceCfg.header.retVal = htonl(retVal);
	netRetDeviceCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetDeviceCfg.header.retVal), sendlen-8));
	#ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetDeviceCfg, sendlen, retVal, recvbuff);
    #else
	//zssreturn writen(connfd, (char *)&netRetDeviceCfg, sendlen);
	return connfd.sendBytes( (char *)&netRetDeviceCfg, sendlen,0);
    #endif
}


/*********************************************************************
 * Function: netClientGetDeviceCfgV40
 * Description:get device parameter
 * Input:
 *        connfd - socket connfd 
 *        recvbuff - recevie data buff
 *        pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *********************************************************************/
STATUS netClientGetDeviceCfgV40(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
    NETCMD_HEADER  netCmdHeader;
    struct{
        NETRET_HEADER header;
        NETPARAM_DEVICE_CFG_V40 deviceCfg;
    }netRetDeviceCfg;
    UINT32 retVal;
    int sendlen=0;
    char buf1[80];
    //UINT8 devModel[80];

    sendlen = sizeof(netRetDeviceCfg);
    bzero((char *)&netRetDeviceCfg, sendlen);
    netRetDeviceCfg.header.length = htonl(sendlen);

    memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
    //zss++retVal = verifyNetClientOperation(&netCmdHeader, pClientSockAddr, REMOTESHOWPARAMETER);

	retVal = NETRET_QUALIFIED;
	
    if(retVal == NETRET_QUALIFIED)
    {
        //zss++writeOperationLogEntry(netCmdHeader.userID, MINOR_REMOTE_GET_PARM, PARA_DEVICE);

        netRetDeviceCfg.deviceCfg.length = htonl(sizeof(NETPARAM_DEVICE_CFG_V40));
        //memcpy(netRetDeviceCfg.deviceCfg.DVRName,DevName, NAME_LEN);
		netRetDeviceCfg.deviceCfg.DVRName[0]=0x5a;
		netRetDeviceCfg.deviceCfg.DVRName[1]=0x59;
        netRetDeviceCfg.deviceCfg.deviceID = htonl(0x00000058);
        netRetDeviceCfg.deviceCfg.recycleRecord = htonl((UINT32)1);
        //makeProductModel(&bootParms,(char *)devModel);
        memcpy(netRetDeviceCfg.deviceCfg.serialno,SerialNo, strlen(SerialNo));
        netRetDeviceCfg.deviceCfg.softwareVersion = htonl(0x05020000);
        netRetDeviceCfg.deviceCfg.softwareBuildDate = htonl(0x000E0A1C);
        netRetDeviceCfg.deviceCfg.dspSoftwareVersion = htonl(0x00050000);
        netRetDeviceCfg.deviceCfg.dspSoftwareBuildDate = htonl(0x000E0814);
#if defined(DM6467) || defined(HI3515)
        netRetDeviceCfg.deviceCfg.panelVersion = htonl(devHardInfo.panelVersion);
#else
        netRetDeviceCfg.deviceCfg.panelVersion = htonl((UINT32)0);
#endif
        netRetDeviceCfg.deviceCfg.hardwareVersion = htonl(0);
        netRetDeviceCfg.deviceCfg.alarmInNums = (UINT8)1;
        netRetDeviceCfg.deviceCfg.alarmOutNums = (UINT8)1;
//#ifdef HI3515	//now DM6467 & HI3515 are same 
        netRetDeviceCfg.deviceCfg.rs232Nums = 1;
        netRetDeviceCfg.deviceCfg.rs485Nums = 1;
//#else
//        netRetDeviceCfg.deviceCfg.rs232Nums = 1;
//        netRetDeviceCfg.deviceCfg.rs485Nums = 1;
//#endif
        netRetDeviceCfg.deviceCfg.netIfNums = 1;
        netRetDeviceCfg.deviceCfg.hdiskCtrlNums = 0;
        netRetDeviceCfg.deviceCfg.hdiskNums = 0;
        netRetDeviceCfg.deviceCfg.devType = 0;
        netRetDeviceCfg.deviceCfg.channelNums = (UINT8)1;
        netRetDeviceCfg.deviceCfg.firstChanNo = 1;
        netRetDeviceCfg.deviceCfg.decodeChans = (UINT8)0;
        netRetDeviceCfg.deviceCfg.vgaNums = 0;
        netRetDeviceCfg.deviceCfg.usbNums = 0;
        netRetDeviceCfg.deviceCfg.auxOutNum = 0;
        netRetDeviceCfg.deviceCfg.audioNum = 1;
        netRetDeviceCfg.deviceCfg.ipChanNum = 0;
        netRetDeviceCfg.deviceCfg.bESataFun = 0;
		netRetDeviceCfg.deviceCfg.supportAbility = 0;
		#ifdef ABILITY 
		netRetDeviceCfg.deviceCfg.supportAbility |= 0x4;   /* support compression ability */
        netRetDeviceCfg.deviceCfg.bySupport1 |= 0x1;    /* support SNMP_V3 */
		#endif
        NET_INFO(("alarmIn = %d, alarmOut = %d, hdiskCtrl = %d, hdisk = %d, enc = %d, dec = %d\n",
       		 	netRetDeviceCfg.deviceCfg.alarmInNums, netRetDeviceCfg.deviceCfg.alarmOutNums,
        		netRetDeviceCfg.deviceCfg.hdiskCtrlNums, netRetDeviceCfg.deviceCfg.hdiskNums,
        		netRetDeviceCfg.deviceCfg.channelNums, netRetDeviceCfg.deviceCfg.decodeChans));

		netRetDeviceCfg.deviceCfg.bESataFun=0x0;          /* eSATA的默认用途，0-默认录像，1-默认备份 */
    	netRetDeviceCfg.deviceCfg.bEnableIPCPnp=0x0;      /* 0-不支持即插即用，1-支持即插即用 */
	
    	netRetDeviceCfg.deviceCfg.byStorageMode=0x1; //0-盘组模式,1-磁盘配额
    	netRetDeviceCfg.deviceCfg.bySupport1=0x1;   //能力，位与结果为0表示不支持，1表示支持
                        //bySupport1 & 0x1, 支持 SNMP v30
                        //bySupport1 & 0x2, 支持区分回放和下载
    	netRetDeviceCfg.deviceCfg.wDevType=htons((UINT16)0x001F);//设备型号
		netRetDeviceCfg.deviceCfg.byDevTypeName[0]=0x5a;
		netRetDeviceCfg.deviceCfg.byDevTypeName[1]=0x59;

	}

    netRetDeviceCfg.header.retVal = htonl(retVal);
    netRetDeviceCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetDeviceCfg.header.retVal), sendlen-8));
    #ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetDeviceCfg, sendlen, retVal, recvbuff);
    #else
	//zss++ writen(connfd, (char *)&netRetDeviceCfg, sendlen);
	return connfd.sendBytes((char *)&netRetDeviceCfg, sendlen,0);
    #endif
}


/***********************************************************************
 * Function: netClientGetCompressCfg
 * Description: get compress config param
 * Input: 
 *		 connfd - socket connfd 
 *       recvbuff - recevie data buff
 *       pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 ***********************************************************************/
STATUS netClientGetCompressCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_CHAN_HEADER netGetChanCfg;
	int chan;
	struct{
		NETRET_HEADER header;
		NETPARAM_COMPRESS_CFG_V30 compressCfg;
	}netRetCompressCfg;
	UINT32 retVal;
	int sendlen;
	
	int maxIpCount = 1;

	sendlen = sizeof(netRetCompressCfg);
	bzero((char *)&netRetCompressCfg, sendlen);
	netRetCompressCfg.header.length = htonl(sendlen);

	memcpy((char *)&netGetChanCfg, recvbuff, sizeof(NETCMD_CHAN_HEADER));
	chan = netGetChanCfg.channel = ntohl(netGetChanCfg.channel);
	//chan = getMatchChan(chan);
	
	//if(checkNetChanValid(chan) != OK)
	if(chan!=1)
	{
		NET_ERR(("Invalid channel %d\n", chan));
		retVal = NETRET_NO_CHANNEL;
	}
	else
	{
		#if 0
		retVal = verifyNetClientOperation(&(netGetChanCfg.header), pClientSockAddr, REMOTESHOWPARAMETER);
		retVal = NETRET_QUALIFIED;
		if(retVal == NETRET_QUALIFIED)
		{
			writeOperationLogEntry(netGetChanCfg.header.userID, MINOR_REMOTE_GET_PARM, PARA_ENCODE);
			
			if(isAnalogChan(chan))
			{
				netGetAnalogCompressCfgV30(chan, &netRetCompressCfg.compressCfg);
			}
			else
			{
				if(netGetIpCompressCfgV30(chan,&netRetCompressCfg.compressCfg) != OK)
				{
					NET_ERR(("netGetIpCompressCfgV30 failed!\n"));
					retVal = NETRET_DVR_OPER_FAILED;
				}
			}
		}
		#endif
		
	}
	retVal = NETRET_QUALIFIED;
	char tempString[]={ 0x00,0x00,0x00,0x74,0x03,0x13,0x00,0x02,0x00,0x00,0x00,0x17,0x00,0x00,0x00,0x00,
						0x00,0x32,0x02,0x00,0x01,0x02,0x01,0x00,0x00,0x04,0x32,0x02,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x02,0x00,0x00,0x00,0x0F,
						0x00,0x00,0x00,0x00,0x00,0x32,0x02,0x00,0x01,0x02,0x01,0x00,0x00,0x04,0x32,0x02,
						0x00,0x00,0x00,0x00};
	memcpy(&netRetCompressCfg.compressCfg,tempString,sizeof(tempString));
	
	netRetCompressCfg.header.retVal = htonl(retVal);
	netRetCompressCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetCompressCfg.header.retVal), sendlen-8));
    #ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetCompressCfg, sendlen, retVal, recvbuff);
    #else
	//zss++return writen(connfd, (char *)&netRetCompressCfg, sendlen);
	return connfd.sendBytes((char *)&netRetCompressCfg, sendlen,0);
    #endif
}



/******************************************************************************
 * Function: netClientGetNetCfg
 * Description:8000 net client get network cfg
 * Input:  
 *		   connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *****************************************************************************/
STATUS netClientGetNetCfg(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_HEADER  netCmdHeader;
	struct{
		NETRET_HEADER header;
		NETPARAM_NETWORK_CFG networkCfg;
	}netRetNetworkCfg;
	UINT32 retVal;
	int sendlen;
	//NETWORK *pNetCfg;
	UINT32 addr;

	sendlen = sizeof(netRetNetworkCfg);
	bzero((char *)&netRetNetworkCfg, sendlen);
	netRetNetworkCfg.header.length = htonl(sendlen);

	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	//zss++retVal = verifyNetClientOperation(&netCmdHeader, pClientSockAddr, REMOTESHOWPARAMETER);
	retVal = NETRET_QUALIFIED;
	#if 0
	if(retVal == NETRET_QUALIFIED)
	{
		//zss++writeOperationLogEntry(netCmdHeader.userID, MINOR_REMOTE_GET_PARM, PARA_NETWORK);

		pNetCfg = &(pDevCfgParam->networkPara);

		netRetNetworkCfg.networkCfg.length = htonl(sizeof(NETPARAM_NETWORK_CFG));

		//ethercfg
		if (pNetCfg->bUseDhcp == 1)
		{
			netRetNetworkCfg.networkCfg.etherCfg[0].devIp = htonl(0);
		}
		else
		{
	#ifdef DVS65
			addr = get_dhcp_ipaddr();
			if (addr == 0)
			{
				addr = getDvrCfgIpAddr();
			}
			netRetNetworkCfg.networkCfg.etherCfg[0].devIp = htonl(addr);
	#else
			netRetNetworkCfg.networkCfg.etherCfg[0].devIp = htonl(pNetCfg->etherNet[0].ipAddress.v4.s_addr);
	#endif
		}
	#ifdef DVS65
		addr = get_dhcp_netmask();
		if (addr == 0)
		{
			addr = getDevCfgNetMask();
		}
		netRetNetworkCfg.networkCfg.etherCfg[0].devIpMask = htonl(addr);
	#else
		netRetNetworkCfg.networkCfg.etherCfg[0].devIpMask = htonl(pNetCfg->etherNet[0].ipMask.v4.s_addr);	
	#endif
		if(pNetCfg->etherNet[0].mediaType == NET_IF_1000M_FULL)
		{
			netRetNetworkCfg.networkCfg.etherCfg[0].mediaType = htonl(6);
		}
		else if(pNetCfg->etherNet[0].mediaType == NET_IF_AUTO)
		{
			netRetNetworkCfg.networkCfg.etherCfg[0].mediaType = htonl(5);
		}
		else
		{
			netRetNetworkCfg.networkCfg.etherCfg[0].mediaType = htonl(pNetCfg->etherNet[0].mediaType);
		}
		netRetNetworkCfg.networkCfg.etherCfg[0].ipPortNo = htons((UINT16)pNetCfg->etherNet[0].ipPortNo);
		memcpy(netRetNetworkCfg.networkCfg.etherCfg[0].macAddr, pNetCfg->etherNet[0].macAddr, MACADDR_LEN);

		//normal
		//V30 兼容V20接口
		netRetNetworkCfg.networkCfg.manageHostIp = htonl(pNetCfg->alarmHostIpAddr.v4.s_addr);
		netRetNetworkCfg.networkCfg.manageHostPort =  htons((UINT16)pNetCfg->alarmHostIpPort);
		netRetNetworkCfg.networkCfg.httpPort = htons(pNetCfg->httpPortNo);
		netRetNetworkCfg.networkCfg.ipResolverIpAddr = htonl(pNetCfg->ipResolverAddr.v4.s_addr);
		netRetNetworkCfg.networkCfg.mcastAddr = htonl(pNetCfg->multicastIpAddr.v4.s_addr);
	#ifdef DVS65
		if (isStartPPPoE())
		{
			netRetNetworkCfg.networkCfg.gatewayIp = htonl(getDevCfgGateway());
		}
		else
		{
			netRetNetworkCfg.networkCfg.gatewayIp = htonl(getCurrDevGateway());
		}
	#else
		netRetNetworkCfg.networkCfg.gatewayIp = htonl(pNetCfg->gatewayIpAddr.v4.s_addr);
	#endif

		//nfs
		netRetNetworkCfg.networkCfg.nfsIp = htonl(pNetCfg->nfsDiskParam[0].nfsHostIPaddr.v4.s_addr);
		memcpy(netRetNetworkCfg.networkCfg.nfsDirectory, pNetCfg->nfsDiskParam[0].nfsDirectory, PATHNAME_LEN);

		//PPPoE
		netRetNetworkCfg.networkCfg.bEnablePPPoE = htonl(pDevCfgParam->pppoePara.enablePPPoE);
		memcpy(netRetNetworkCfg.networkCfg.pppoeName, pDevCfgParam->pppoePara.username, NAME_LEN);
		memcpy(netRetNetworkCfg.networkCfg.pppoePassword, pDevCfgParam->pppoePara.password, PASSWD_LEN);
		netRetNetworkCfg.networkCfg.pppoeIp = htonl(getPPPoeLocalIp());
	}
	#endif
	unsigned char tempString[]={0x00,0x00,0x01,0x08,0x82,0x01,0xA8,0xC0,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x05,
						0x1F,0x40,0x00,0x00,0xC0,0x56,0xE3,0xB3,0xF9,0x1B,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x01,0x01,0xA8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	memcpy(&netRetNetworkCfg.networkCfg,tempString,sizeof(tempString));

	netRetNetworkCfg.header.retVal = htonl(retVal);
	netRetNetworkCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetNetworkCfg.header.retVal), sendlen-8));
	
	#ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetNetworkCfg, sendlen, retVal, recvbuff);
    #else
	//zss++return writen(connfd, (char *)&netRetNetworkCfg, sendlen);
	return connfd.sendBytes((char *)&netRetNetworkCfg, sendlen,0);
    #endif
}

/***************************************************************************
 * Function: netClientGetNetCfgV30
 * Description:9000 net client get network  cfg
 * Input:  
 *	   connfd - socket connfd 
 *       recvbuff - recevie data buff
 *       pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 ***************************************************************************/
STATUS netClientGetNetCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	 
	NETCMD_HEADER  netCmdHeader;
	struct{
		NETRET_HEADER header;
		NETPARAM_NETWORK_CFG_V30 networkCfg;
	}netRetNetworkCfg;
	UINT32 retVal;
	int sendlen;
	//NETWORK *pNetCfg;
	//PPPOEPARA *pPPPoECfg;
	UINT32 addr;
    UINT32 prefix1, prefix2;
    struct in6_addr ipv61, ipv62;

	sendlen = sizeof(netRetNetworkCfg);
	bzero((char *)&netRetNetworkCfg, sendlen);
	netRetNetworkCfg.header.length = htonl(sendlen);

	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	//zss++retVal = verifyNetClientOperation(&netCmdHeader, pClientSockAddr, REMOTESHOWPARAMETER);
	retVal = NETRET_QUALIFIED;

	if(retVal == NETRET_QUALIFIED)
	{
		//zss++writeOperationLogEntry(netCmdHeader.userID, MINOR_REMOTE_GET_PARM, PARA_NETWORK);

		//zss++pNetCfg = &(pDevCfgParam->networkPara);
		
		netRetNetworkCfg.networkCfg.length = htonl(sizeof(NETPARAM_NETWORK_CFG_V30));

		//etherNet
	#ifdef DVS65
		addr = get_dhcp_ipaddr();
		if (addr == 0)
		{
			addr = getDvrCfgIpAddr();
		}
		netRetNetworkCfg.networkCfg.etherCfg[0].devIp.v4.s_addr = htonl(addr);
		addr = get_dhcp_netmask();
		if (addr == 0)
		{
			addr = getDevCfgNetMask();
		}
		netRetNetworkCfg.networkCfg.etherCfg[0].devIpMask.v4.s_addr = htonl(addr);
	#else
		netRetNetworkCfg.networkCfg.etherCfg[0].devIp.v4.s_addr = htonl(0x6c01a8c0);
		netRetNetworkCfg.networkCfg.etherCfg[0].devIpMask.v4.s_addr = htonl(0x00ffffff);
	#endif
	#ifdef SUPPORT_IPV6
		if(!get_ipv6addr_num(LOCAL_INTERFACE, &ipv61, &prefix1, &ipv62, &prefix2))
		{
			netRetNetworkCfg.networkCfg.etherCfg[0].devIp.v6 = ipv61;
			if(!convertIPv6Prefix2Netmask(prefix1, &ipv61))
			{
				netRetNetworkCfg.networkCfg.etherCfg[0].devIpMask.v6 = ipv61;
			}
		}
	#endif
		netRetNetworkCfg.networkCfg.etherCfg[0].mediaType = htonl((UINT32)5);
		netRetNetworkCfg.networkCfg.etherCfg[0].ipPortNo = htons(8000);
		netRetNetworkCfg.networkCfg.etherCfg[0].mtu = htons(1500);
		unsigned char macAddr[6]={0x90,0x2B,0x34,0xc9,0xEb,0x3A};
		memcpy(netRetNetworkCfg.networkCfg.etherCfg[0].macAddr, macAddr, MACADDR_LEN);

		netRetNetworkCfg.networkCfg.manageHost1IpAddr.v4.s_addr = htonl(0);
		netRetNetworkCfg.networkCfg.manageHost2IpAddr.v4.s_addr  = htonl(0);
		netRetNetworkCfg.networkCfg.alarmHostIpAddr.v4.s_addr = htonl(0);
		netRetNetworkCfg.networkCfg.manageHost1Port =  htons(0);
		netRetNetworkCfg.networkCfg.manageHost2Port =  htons(0);
		netRetNetworkCfg.networkCfg.alarmHostIpPort =  htons(0);
		netRetNetworkCfg.networkCfg.bUseDhcp = 0;

		netRetNetworkCfg.networkCfg.dnsServer1IpAddr.v4.s_addr = htonl(0x08080808);
		netRetNetworkCfg.networkCfg.dnsServer2IpAddr.v4.s_addr = htonl(0x0);

		char ipResolver[MAX_DOMAIN_NAME]={0,};
		memcpy(netRetNetworkCfg.networkCfg.ipResolver,ipResolver,MAX_DOMAIN_NAME);
		netRetNetworkCfg.networkCfg.ipResolverPort =  htons(0x1B9E);
		
		netRetNetworkCfg.networkCfg.httpPortNo =  htons(0x0050);
		
		netRetNetworkCfg.networkCfg.multicastIpAddr.v4.s_addr  = htonl(0x010100ef);
	#ifdef DVS65
		if (isStartPPPoE())
		{
			netRetNetworkCfg.networkCfg.gatewayIpAddr.v4.s_addr  = htonl(getDevCfgGateway());
		}
		else
		{
			netRetNetworkCfg.networkCfg.gatewayIpAddr.v4.s_addr  = htonl(getCurrDevGateway());
		}
	#else
		netRetNetworkCfg.networkCfg.gatewayIpAddr.v4.s_addr  = htonl(0x0108a8c0);
	#endif
	#ifdef SUPPORT_IPV6
		if(!get_ipv6_gateway_num(LOCAL_INTERFACE, &ipv61))
		{
			netRetNetworkCfg.networkCfg.gatewayIpAddr.v6 = ipv61;
		}

        {
            netRetNetworkCfg.networkCfg.multicastIpAddr.v6 = pNetCfg->multicastIpAddr.v6;
            netRetNetworkCfg.networkCfg.alarmHostIpAddr.v6 = pNetCfg->alarmHostIpAddr.v6;
            netRetNetworkCfg.networkCfg.dnsServer1IpAddr.v6 = pNetCfg->dnsServer1IpAddr.v6;        
            netRetNetworkCfg.networkCfg.dnsServer2IpAddr.v6 = pNetCfg->dnsServer2IpAddr.v6;
        }
    #endif
		//pPPPoECfg = &(pDevCfgParam->pppoePara);
		//netRetNetworkCfg.networkCfg.PPPoECfg.enablePPPoE = htonl((UINT32)pPPPoECfg->enablePPPoE);
		//memcpy(netRetNetworkCfg.networkCfg.PPPoECfg.PPPoEUser, pPPPoECfg->username,NAME_LEN);
		//memcpy(netRetNetworkCfg.networkCfg.PPPoECfg.PPPoEPassword, pPPPoECfg->password,PASSWD_LEN);
		netRetNetworkCfg.networkCfg.PPPoECfg.PPPoEIp.v4.s_addr = htonl(0x0);
	}

	netRetNetworkCfg.header.retVal = htonl(retVal);
	netRetNetworkCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetNetworkCfg.header.retVal), sendlen-8));
    #ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetNetworkCfg, sendlen, retVal, recvbuff);
    #else
	//return writen(connfd, (char *)&netRetNetworkCfg, sendlen);
	return connfd.sendBytes((char *)&netRetNetworkCfg, sendlen,0);
	#endif
}


/******************************************************************************
 * Function: netClientGetRtspPort
 * Description: net client get rtsp port
 * Input:
 *		   connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *****************************************************************************/
STATUS netClientGetRtspPort(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_HEADER  netCmdHeader;
	struct{
		NETRET_HEADER header;
		NETPARAM_RTSP_CFG rtspCfg;
	}netCmdRtspCfg;
	UINT32 retVal;
	int sendlen, i;

	sendlen = sizeof(netCmdRtspCfg);
	bzero((char *)&netCmdRtspCfg, sendlen);
	netCmdRtspCfg.header.length = htonl(sendlen);

	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	//zss++retVal = verifyNetClientOperation(&netCmdHeader, pClientSockAddr, REMOTESHOWPARAMETER);
	retVal = NETRET_QUALIFIED;
	if(retVal == NETRET_QUALIFIED)
	{
		//zss++writeOperationLogEntry(netCmdHeader.userID, MINOR_REMOTE_GET_PARM, PARA_NETWORK);
		netCmdRtspCfg.rtspCfg.length = htonl(sizeof(NETPARAM_RTSP_CFG));
		netCmdRtspCfg.rtspCfg.rtspPort = htons(554);
        NET_INFO(("GET RTSP PORT %d\n",554));
	}

	netCmdRtspCfg.header.retVal = htonl(retVal);
	netCmdRtspCfg.header.checkSum = htonl(checkByteSum((char *)&(netCmdRtspCfg.header.retVal), sendlen - 8));
    #ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netCmdRtspCfg, sendlen, retVal, recvbuff);
    #else
    //zss++return writen(connfd, (char *)&netCmdRtspCfg, sendlen);
	return connfd.sendBytes((char *)&netCmdRtspCfg,sendlen,0);
    #endif
}

/******************************************************************************
 * Function: netClientReloveCmd11000
 * Description: net client get rtsp port
 * Input:
 *		   connfd - socket connfd 
 *         recvbuff - recevie data buff
 *         pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 *****************************************************************************/
STATUS netClientReloveCmd11000(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NET_CMD11000_REQ  netCmd11000Req;
	NETRET_HEADER header;

	UINT32 retVal;
	int sendlen, i;
	
	memcpy((char *)&netCmd11000Req, recvbuff, sizeof(NET_CMD11000_REQ));

	NET_INFO(("netClientReloveCmd11000  cmd0 0x%x. cmd1=0x%x\n",netCmd11000Req.cmd0,netCmd11000Req.cmd1));
	int cmd0= ntohl(netCmd11000Req.cmd0);
	int cmd1 = ntohl(netCmd11000Req.cmd1);
	switch(cmd0)
	{
		case 0x1:
			NET_INFO(("netClientReloveCmd11000  0x01.\n"));
			bzero((char *)&header, sendlen);
			sendlen=sizeof(cmd11000_01);
			header.length=htonl(sendlen);
			header.retVal = htonl(1);
			memcpy(cmd11000_01,&header,sizeof(header));
			header.checkSum = htonl(checkByteSum((char *)cmd11000_01+8, sendlen - 8));
			memcpy(cmd11000_01,&header,sizeof(header));
			return connfd.sendBytes((char *)cmd11000_01,sendlen,0);
			break;
		case 0x5:
			NET_INFO(("netClientReloveCmd11000  0x05.\n"));
			bzero((char *)&header, sendlen);
			sendlen=sizeof(cmd11000_05);
			header.length=htonl(sendlen);
			header.retVal = htonl(1);
			memcpy(cmd11000_05,&header,sizeof(header));
			header.checkSum = htonl(checkByteSum((char *)cmd11000_05+8, sendlen - 8));
			memcpy(cmd11000_05,&header,sizeof(header));
			return connfd.sendBytes((char *)cmd11000_05,sendlen,0);
			break;
		case 0x8:
			NET_INFO(("netClientReloveCmd11000  0x08.\n"));
			bzero((char *)&header, sendlen);
			sendlen=sizeof(cmd11000_08);
			header.length=htonl(sendlen);
			header.retVal = htonl(1);
			memcpy(cmd11000_08,&header,sizeof(header));
			header.checkSum = htonl(checkByteSum((char *)cmd11000_08+8, sendlen - 8));
			memcpy(cmd11000_08,&header,sizeof(header));
			return connfd.sendBytes((char *)cmd11000_08,sendlen,0);
			break;
		case 0xe:
			sendlen=sizeof(cmd11000_0E);
			header.length=htonl(sendlen);
			header.retVal = htonl(1);
			memcpy(cmd11000_0E,&header,sizeof(header));
			NET_INFO(("netClientReloveCmd11000 cmd11000_0E\n"));
			return connfd.sendBytes((char *)cmd11000_0E,sendlen,0);
			break;
		case 0x11:
			bzero((char *)&header, sendlen);
			NET_INFO(("netClientReloveCmd11000  0x011 %d\n",netCmd11000Req.cmd1));
			if(cmd1==0X3C50545A)
			{
				sendlen=sizeof(cmd11000_11_3C50545A);
				header.length=htonl(sendlen);
				header.retVal = htonl(1);
				memcpy(cmd11000_11_3C50545A,&header,sizeof(header));
				header.checkSum = htonl(checkByteSum((char *)cmd11000_11_3C50545A+8, sendlen - 8));
				memcpy(cmd11000_11_3C50545A,&header,sizeof(header));
				return connfd.sendBytes((char *)cmd11000_11_3C50545A,sendlen,0);
			}
			else if(cmd1==0X3C457665)
			{
				sendlen=sizeof(cmd11000_11_3C457665);
				header.length=htonl(sendlen);
				header.retVal = htonl(1);
				memcpy(cmd11000_11_3C457665,&header,sizeof(header));
				header.checkSum = htonl(checkByteSum((char *)cmd11000_11_3C457665+8, sendlen - 8));
				memcpy(cmd11000_11_3C457665,&header,sizeof(header));
				return connfd.sendBytes((char *)cmd11000_11_3C457665,sendlen,0);
			}
			else
				return -1;
			break;
		default:
			//NET_INFO(("netClientReloveCmd11000 default\n"));
			//return connfd.sendBytes((char *)tempString,sizeof(tempString),0);
			break;
	}

}

/**********************************************************************
 * Function:  netClientSetDevTime
 * Description: set device time
 * Input: 
 *		 connfd - socket connfd 
 *       recvbuff - recevie data buff
 *       pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 **********************************************************************/
STATUS netClientSetDevTime(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	UINT32 retVal;
	if(1)
	{
		retVal = NETRET_QUALIFIED;
	}
	else
	{
		retVal = NETRET_NO_USERID;
	}

	NETRET_HEADER  netRetHeader;
	int sendlen;

	sendlen = sizeof(NETRET_HEADER);
	bzero((char *)&netRetHeader, sendlen);
	netRetHeader.length = htonl(sendlen);
	netRetHeader.retVal = htonl(retVal);
	netRetHeader.checkSum = htonl(checkByteSum((char *)&(netRetHeader.retVal), sendlen-8));
	//zss++return writen(connfd, (char *)&netRetHeader, sendlen);
	return connfd.sendBytes((char *)&netRetHeader, sendlen,0);
}

/***********************************************************************
 * Function: netClientGetPicCfg
 * Description:set pic parameter
 * Input: 
 *		 connfd - socket connfd 
 *       recvbuff - recevie data buff
 *       pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 **********************************************************************/
STATUS netClientGetPicCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	
	NETCMD_CHAN_HEADER netGetChanCfg;
	int chan;
	struct{
		NETRET_HEADER header;
		NETPARAM_PIC_CFG_V30 picCfg;
	}netRetPicCfg;
	UINT32 retVal= NETRET_QUALIFIED;;
	int sendlen;
	int maxIpCount = 1;

	unsigned char tempString[]={ 0x00,0x00,0x07,0xB0,0x43,0x61,0x6D,0x65,0x72,0x61,0x20,0x30,0x31,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x00,0x02,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0xFF,0x01,0x01,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x22,0x01,0x36,
						0x01,0x29,0x00,0xDC,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
						0x00,0x00,0x00,0x20,0x01,0x01,0x04,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	memcpy(&netRetPicCfg.picCfg,tempString,sizeof(tempString));
	sendlen = sizeof(netRetPicCfg);
	bzero((char *)&netRetPicCfg, sendlen);
	netRetPicCfg.header.length = htonl(sendlen);
	netRetPicCfg.header.retVal = htonl(retVal);
	netRetPicCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetPicCfg.header.retVal), sendlen-8));

	#ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetPicCfg, sendlen, retVal, recvbuff);
    #else
	//zss++return writen(connfd, (char *)&netRetPicCfg, sendlen);
	return connfd.sendBytes((char *)&netRetPicCfg,sendlen,0);
    #endif
	
}


/**********************************************************************
 * Function: netClientGetAlarmInCfg
 * Description:get alarmIn config param
 * Input: 
 *		 connfd - socket connfd 
 *       recvbuff - recevie data buff
 *       pClientSockAddr - client socket address(not need)
 * Output:  N/A
 * Return:  OK if successful, otherwise return error status number
 **********************************************************************/
STATUS netClientGetAlarmInCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	NETCMD_CHAN_HEADER netGetChanCfg;
	struct{
		NETRET_HEADER header;
		NETPARAM_ALARMIN_CFG_V30 alarmInCfg;
	}netRetAlarmInCfg;
	UINT32 retVal;
	int ipChan;
	int sendlen, alarmInNum;
	
	sendlen = sizeof(netRetAlarmInCfg);
	bzero((char *)&netRetAlarmInCfg, sendlen);
	netRetAlarmInCfg.header.length = htonl(sendlen);

	memcpy((char *)&netGetChanCfg, recvbuff, sizeof(NETCMD_CHAN_HEADER));
	alarmInNum = netGetChanCfg.channel = ntohl(netGetChanCfg.channel);	/* alarmIn chan */

	if(0)
	{
		retVal = NETRET_NO_ALARMIN;
		NET_ERR(("Invalid alarmIn channel %d\n", alarmInNum));
	}
	else
	{
		retVal = NETRET_QUALIFIED;
		char tempString[]={
							0x00,0x00,0x03,0x6C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,
							0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,
							0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
						  };
		memcpy(&netRetAlarmInCfg.alarmInCfg,tempString,sizeof(tempString));
		
	}

	netRetAlarmInCfg.header.retVal = htonl(retVal);
	netRetAlarmInCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetAlarmInCfg.header.retVal), sendlen-8));
	#ifdef NET_PUSH_SDK
    return net_write_resp(connfd, (char *)&netRetAlarmInCfg, sendlen, retVal, recvbuff);
    #else
	//zss++return writen(connfd, (char *)&netRetAlarmInCfg, sendlen);
	return connfd.sendBytes((char *)&netRetAlarmInCfg,sendlen,0);
    #endif
}

STATUS netClientRestoreCfg(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr)
{
	int retVal;
	if(1)
	{
		retVal = NETRET_QUALIFIED;
	}
	else
	{
		retVal = NETRET_NO_USERID;
	}

	struct{
		NETRET_HEADER header;
		UINT32 ret;
	}netRetRestoreCfg;
	
	int sendlen;
	sendlen = sizeof(netRetRestoreCfg);
	bzero((char *)&netRetRestoreCfg, sendlen);
	netRetRestoreCfg.header.length = htonl(sendlen);
	netRetRestoreCfg.header.retVal = htonl(retVal);
	netRetRestoreCfg.header.checkSum = htonl(checkByteSum((char *)&(netRetRestoreCfg.header.retVal), sendlen-8));
	//zss++return writen(connfd, (char *)&netRetHeader, sendlen);
	return connfd.sendBytes((char *)&netRetRestoreCfg, sendlen,0);

}

STATUS reloveOnePacket(StreamSocket  &connfd,char *recvbuff,UINT32 bufferSize)
{
	NETCMD_HEADER netCmdHeader;
	UINT32 cmdLength, leftLen;
	INT32  retVal=-1;
	struct sockaddr_in  clientSockAddr, *pClientSockAddr;
	memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
	netCmdHeader.netCmd = ntohl(netCmdHeader.netCmd);
	NET_INFO(("netCmdHeader.netCmd = 0x%0x\n", netCmdHeader.netCmd));
	switch(netCmdHeader.netCmd)
	{
	case NETCMD_LOGIN:           			/*user login*/			
		NET_INFO(("NETCMD_LOGIN.\n"));
		retVal = netClientLogin(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_RELOGIN:          			/*user relogin*/
		NET_INFO(("NETCMD_RELOGIN.\n"));
		//retVal = netClientReLogin(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_LOGOUT:	          		/*user logout*/	
		NET_INFO(("NETCMD_LOGOUT.\n"));
		retVal = netClientLogout(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_USEREXCHANGE:     		/*user exchange*/
		NET_INFO(("NETCMD_USEREXCHANGE, time = 0x%x.\n", (int)time(NULL)));
		retVal = netClientUserExchange(connfd, recvbuff, pClientSockAddr);
		break;
	/*====================================================================
	*            				 		parameter config
	* ====================================================================*/	
	case NETCMD_GET_DEVICECFG:  		/*get device config param*/	
		NET_INFO(("NETCMD_GET_DEVICECFG.\n"));
		retVal = netClientGetDeviceCfg(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_DEVICECFG_V40:			/*get device config param*/ 
		NET_INFO(("NETCMD_GET_DEVICECFG_V40.\n"));
		retVal = netClientGetDeviceCfgV40(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_IPCORECFG_V31:        /*get IPC core config param, supports domain name*/
		NET_INFO(("NETCMD_GET_IPCORECFG_V31.\n"));
		//retVal = netClientGetIpCoreCfgV31(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_NETCFG_V30:	    	/*get network config param*/	
		NET_INFO(("NETCMD_GET_NETCFG_V30.\n"));
		retVal = netClientGetNetCfgV30(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_PREVIEWCFG_V30:    	/*get preview config param*/
		NET_INFO(("NETCMD_GET_PREVIEWCFG_V30.\n"));
		//retVal = netClientGetPrevCfgV30(connfd, recvbuff, pClientSockAddr, CHANNEL_MAIN);
		break;
	case NETCMD_GET_NETCFG:	    		/*get network config param*/	
		NET_INFO(("NETCMD_GET_NETCFG.\n"));
		retVal = netClientGetNetCfg(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_RTSPPORT:
		NET_INFO(("NETCMD_GET_RTSPOLDCFG.\n"));
		retVal = netClientGetRtspPort(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_COMPRESSCFG_V30:   /*get compress config param*/
		NET_INFO(("NETCMD_GET_COMPRESSCFG_V30.\n"));
		retVal = netClientGetCompressCfgV30(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_PICCFG_V30:	  	/*get PIC V30 config param*/	
		NET_INFO(("NETCMD_GET_PICCFG_V30.\n"));
		retVal = netClientGetPicCfgV30(connfd, recvbuff, pClientSockAddr);
		break;
	case 0x11000:
		NET_INFO(("NETCMD_GET_11000.\n"));
		retVal = netClientReloveCmd11000(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_SET_TIMECFG:       		/*set time config param*/
		NET_INFO(("NETCMD_SET_TIMECFG.\n"));
		retVal = netClientSetDevTime(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_GET_ALARMINCFG_V30:    	/*get alarm in config param*/
		NET_INFO(("NETCMD_GET_ALARMINCFG_V30.\n"));
		retVal = netClientGetAlarmInCfgV30(connfd, recvbuff, pClientSockAddr);
		break;
	case NETCMD_RESTORE_CFG:				/*restore config*/	
		NET_INFO(("NETCMD_RESTORE_CFG.\n"));
		retVal = netClientRestoreCfg(connfd, recvbuff, pClientSockAddr);
		break;
	default:
		retVal=-1;
		break;
	}		
	return retVal;
}

STATUS relovePacket(StreamSocket  &connfd,FIFOBuffer &fifoBuffer)
{
	char *precvbuff;
	NETCMD_HEADER netCmdHeader;
	UINT32 cmdLength, leftLen;
	INT32  retVal=-1;
	struct sockaddr_in  clientSockAddr, *pClientSockAddr;
	char recvbuff[BUFFER_SIZE]={0};
	std::size_t bufferSize=fifoBuffer.used();
	if(bufferSize<4)
		return -1;
	memcpy(recvbuff,fifoBuffer.buffer().begin(),bufferSize);
	if(bufferSize>0)
		fifoBuffer.drain(bufferSize);
	cmdLength=*(UINT32 *)recvbuff;
	cmdLength=ntohl(cmdLength);
	
	NET_INFO(("Command size %d,Command length = %d :data:%s\n",bufferSize,cmdLength,recvbuff));
	if(cmdLength>=24 && cmdLength<=BUFFER_SIZE-sizeof(struct in6_addr))
	{
		/* valid command length */
		leftLen = cmdLength - 4;
		if(bufferSize <= leftLen)
		{
			NET_ERR(("readn() length error: %d, %d\n", bufferSize-4, leftLen));
			return -2;
		}
		precvbuff = recvbuff;
		*(UINT32 *)precvbuff = htonl(cmdLength);
		memcpy((char *)&netCmdHeader, recvbuff, sizeof(NETCMD_HEADER));
		netCmdHeader.netCmd = ntohl(netCmdHeader.netCmd);
		NET_INFO(("netCmdHeader.netCmd = 0x%0x\n", netCmdHeader.netCmd));
		switch(netCmdHeader.netCmd)
		{
		case NETCMD_LOGIN:           			/*user login*/			
			NET_INFO(("NETCMD_LOGIN.\n"));
			retVal = netClientLogin(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_RELOGIN:          			/*user relogin*/
			NET_INFO(("NETCMD_RELOGIN.\n"));
			//retVal = netClientReLogin(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_LOGOUT:	          		/*user logout*/	
			NET_INFO(("NETCMD_LOGOUT.\n"));
			retVal = netClientLogout(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_USEREXCHANGE:     		/*user exchange*/
			NET_INFO(("NETCMD_USEREXCHANGE, time = 0x%x.\n", (int)time(NULL)));
			retVal = netClientUserExchange(connfd, recvbuff, pClientSockAddr);
			break;
		/*====================================================================
		*            				 		parameter config
		* ====================================================================*/	
		case NETCMD_GET_DEVICECFG:  		/*get device config param*/	
			NET_INFO(("NETCMD_GET_DEVICECFG.\n"));
			retVal = netClientGetDeviceCfg(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_DEVICECFG_V40:			/*get device config param*/ 
			NET_INFO(("NETCMD_GET_DEVICECFG_V40.\n"));
			retVal = netClientGetDeviceCfgV40(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_IPCORECFG_V31:        /*get IPC core config param, supports domain name*/
			NET_INFO(("NETCMD_GET_IPCORECFG_V31.\n"));
			//retVal = netClientGetIpCoreCfgV31(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_NETCFG_V30:	    	/*get network config param*/	
			NET_INFO(("NETCMD_GET_NETCFG_V30.\n"));
			retVal = netClientGetNetCfgV30(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_PREVIEWCFG_V30:    	/*get preview config param*/
			NET_INFO(("NETCMD_GET_PREVIEWCFG_V30.\n"));
			//retVal = netClientGetPrevCfgV30(connfd, recvbuff, pClientSockAddr, CHANNEL_MAIN);
			break;
		case NETCMD_GET_NETCFG:	    		/*get network config param*/	
			NET_INFO(("NETCMD_GET_NETCFG.\n"));
			retVal = netClientGetNetCfg(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_RTSPPORT:
			NET_INFO(("NETCMD_GET_RTSPOLDCFG.\n"));
			retVal = netClientGetRtspPort(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_COMPRESSCFG_V30:   /*get compress config param*/
			NET_INFO(("NETCMD_GET_COMPRESSCFG_V30.\n"));
			retVal = netClientGetCompressCfgV30(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_PICCFG_V30:	  	/*get PIC V30 config param*/	
			NET_INFO(("NETCMD_GET_PICCFG_V30.\n"));
			retVal = netClientGetPicCfgV30(connfd, recvbuff, pClientSockAddr);
			break;
		case 0x11000:
			NET_INFO(("NETCMD_GET_11000.\n"));
			retVal = netClientReloveCmd11000(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_SET_TIMECFG:       		/*set time config param*/
			NET_INFO(("NETCMD_SET_TIMECFG.\n"));
			retVal = netClientSetDevTime(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_GET_ALARMINCFG_V30:    	/*get alarm in config param*/
			NET_INFO(("NETCMD_GET_ALARMINCFG_V30.\n"));
			retVal = netClientGetAlarmInCfgV30(connfd, recvbuff, pClientSockAddr);
			break;
		case NETCMD_RESTORE_CFG:				/*restore config*/	
			NET_INFO(("NETCMD_RESTORE_CFG.\n"));
			retVal = netClientRestoreCfg(connfd, recvbuff, pClientSockAddr);
			break;
		default:
			break;
		

		}
				
	}
	
	return 0;
}

#endif
