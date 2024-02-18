#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"stylesheet.h"
#include<QApplication>
#include<QString>
#include<QLabel>
#include<QPushButton>
#include<QDateTime>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"initlializationsettingfile.h"
#include"prayertimes.h"
#include"screeninformation.h"
#include<QTimer>
#include"dynamicfontsizelabel.h"
#include"dynamicfontsizepushbutton.h"
#include<QAction>
#include<QMenu>
#include"stylesheet.h"
#include"hijri.h"
#include"databaseconnection.h"
#include<QTextEdit>
#include"socket.h"
#include<QListView>
#include <QComboBox>
#include <QCompleter>
#include <QLineEdit>
#include<QMediaPlayer>
#include <QWidget>
#include <QNetworkAccessManager>
#include<QNetworkConfigurationManager>
#include<QNetworkConfiguration>
#include<QNetworkSession>
#include<wirelesslog.h>
#include <QMessageBox>

namespace Ui {
class MainWindow{};
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
      QString CssFile;
      initlializationSettingFile Settings;
      PrayerTimes prayer_times;
      DatabaseConnection Database;
      QTextEdit *AddingMessageEvent = new QTextEdit(this);
      QMediaPlayer *player= new QMediaPlayer();

           hijri HijriDate;
//           SocketTest test;
           QTcpServer *server;
           QTcpSocket *server1;

          // DatabaseConnection DataBase;
      //--->>> Clock Label and its Properties <<<---//
      QLabel  *ClockLabel= new QLabel(this);
      QLabel  *GregorianLabel= new QLabel(this);
      QLabel  *HijriLabel = new QLabel(this);

      //---->> Prayer Time Labels <<----//
      QLabel  *FajerLabel = new QLabel(this);
      QLabel  *FajerTimeLabel = new QLabel(this);
      QLabel  *SharouqLabel = new QLabel(this);
      QLabel  *SharouqTimeLabel = new QLabel(this);
      QLabel  *DhuhrLabel = new QLabel(this);
      QLabel  *DhuhrTimeLabel = new QLabel(this);
      QLabel  *AsrLabel= new QLabel(this);
      QLabel  *AsrTimeLabel= new QLabel(this);
      QLabel  *MagribLabel = new QLabel(this);
      QLabel  *MagribTimeLabel = new QLabel(this);
      QLabel  *IshaLabel = new QLabel(this);
      QLabel  *IshaTimeLabel = new QLabel(this);
      QLabel  *FajerEditLabel= new QLabel(this);
      QLabel  *ShrouqEditLabel= new QLabel(this);
      QLabel  *DhuhrEditLabel= new QLabel(this);
      QLabel  *AsrEditLabel= new QLabel(this);
      QLabel  *MagribEditLabel= new QLabel(this);
      QLabel  *IshaEditLabel= new QLabel(this);
      QLabel *iqamahMessageLabel = new QLabel(this);
      QLabel *progress = new QLabel(this);
      // QLabel *IslamicEventTitle = new QLabel(this);
      QString IncPrayer="";
      StyleSheet StyleSheetFile;

      DynamicFontSizeLabel *HadithQuranLabel = new DynamicFontSizeLabel(this);
      DynamicFontSizeLabel *HadithQuranTabLabel = new DynamicFontSizeLabel(this);

      QLabel *IslamicEventTitle = new QLabel(this);
      DynamicFontSizeLabel *IslamicEventContent = new DynamicFontSizeLabel(this);
      QPushButton  *ClockAdjustmentplus = new QPushButton(this);
      QPushButton  *ClockAdjustmentminus = new QPushButton(this);
      QPushButton  *PrayerFajerAdjustPlus = new QPushButton(this);
      QPushButton  *PrayerFajerAdjustMinus = new QPushButton(this);
      QPushButton  *PrayerSharouqAdjustPlus = new QPushButton(this);
      QPushButton  *PrayerSharouqAdjustMinus = new QPushButton(this);
      QPushButton  *PrayerDhuhrAdjustPlus = new QPushButton(this);
      QPushButton  *PrayerDhuhrAdjustMinus = new QPushButton(this);
      QPushButton  *PrayerAsrAdjustPlus = new QPushButton(this);
      QPushButton  *PrayerAsrAdjustMinus = new QPushButton(this);
      QPushButton  *PrayerMagribAdjustPlus = new QPushButton(this);
      QPushButton  *PrayerMagribAdjustMinus = new QPushButton(this);
      QPushButton  *PrayerIshaAdjustPlus = new QPushButton(this);
      QPushButton  *PrayerIshaAdjustMinus = new QPushButton(this);
      QPushButton  *SaveMessage = new QPushButton(this);
      QLabel       *ClockAdjustmentLabel = new QLabel(this);
      QDateTime t= QDateTime::currentDateTime();
        double plus=1;
        double indexplus=0;
        double minus=1;
        double indexminus=0;
         //---------------->>> temp
         int *addedTimeFajer;
         int *addedTimeShrouq;
         int *addedTimeDhuhr;
         int *addedTimeAsr;
         int *addedTimeMagrib;
         int *addedTimeIsha;
         int addedTimeFajer_v;
         int addedTimeShrouq_v;
         int addedTimeDhuhr_v;
         int addedTimeAsr_v;
         int addedTimeMagrib_v;
         int addedTimeIsha_v;
         int volume=100;
         int *iqamahTimeFajer;
         int *iqamahTimeShrouq;
         int *iqamahTimeDhuhr;
         int *iqamahTimeAsr;
         int *iqamahTimeMagrib;
         int *iqamahTimeIsha;
         int iqamahTimeFajer_v;
         int iqamahTimeShrouq_v;
         int iqamahTimeDhuhr_v;
         int iqamahTimeAsr_v;
         int iqamahTimeMagrib_v;
         int iqamahTimeIsha_v;
         int iqamahCounterDec;

         int *HijriAddedDays;
         int HijriAddedDays_v;

         int iqamahFajerCounter;
         int iqamahDhuhrCounter;
         int iqamahAsrCounter;
         int iqamahMagribCounter;
         int iqamahIshaCounter;

         QNetworkAccessManager *mgr=new  QNetworkAccessManager(this);

         QTime Isha;
         QTime Magrib;
         QTime Asr;
         QTime Dhuhr;
         QTime Shrouq;
         QTime Fajer;
         ScreenInformation Screen;
         QSize  ScreenSize1=Screen.ScreenSize();
         int height=ScreenSize1.height();
         int *index=&height;
         QTimer *timer = new QTimer();
         QTimer *timer1 = new QTimer();
         QTimer *timer2 = new QTimer();
         QTimer *iqamahTimer= new QTimer();
        QString *currentPrayerPtr;
        QString currentPrayer;
        bool *ArabicLang;
        bool v_ArabicLang;
        bool HadithOrQuran;
        int ClockPosition [2];
        int PrayerWidgetPosition[2];
        QString prayerMethod;
    void TodayIslamicEvent(QSize size,int EventPositionX,int EventPositionY);
    void ClockWidget(QSize size,int ClockPositionX,int ClockPositionY);
    void PrayerWidget(QSize size, int PrayerPositionX, int PrayerPositionY, int VSpacing , bool &ArabicLang);
    void PrayerEdit(QSize size, int PositionX,int PositionY);
     //--->>> Clock Label and its Properties <<<---//
    //----->>> Setting Button and its Properties <<<---//
    bool visiblity=false;
    bool PrayerTimeVisible=false;
    bool ClockEditVisible= false;
    bool PrayerEditVisible= false;
    bool iqamahActive = false;
    bool HijriEditShow =false;
    bool ThemaChange=false;
    bool a_fajer,a_dhuhr,a_asr,a_mgrib,a_isha=false;
    bool sleep_no,sleep_def=false;

       QMenu *SettingMenu= new QMenu(this);
       QMenu *PrayersMenu = SettingMenu->addMenu("Prayer");
       QMenu *TimeMenu = SettingMenu->addMenu("Time");
       QMenu *Language = SettingMenu->addMenu("Language");
       QMenu *InterfaceThema = SettingMenu->addMenu("Thema");
       QMenu *FactoryResetMenu= SettingMenu->addMenu("Reset Factory");
       QMenu *AddingMessageMenu = SettingMenu->addMenu("Messages");
       QMenu *AzanSettings = SettingMenu->addMenu("Azan Settings");
       QMenu *AzanSettings_azan = AzanSettings->addMenu("Prayer Settings");
       QMenu *AzanSettings_Mothen = AzanSettings->addMenu("Moethn Settings");
       QMenu *Sleeping_Mode=SettingMenu->addMenu("Sleeping Mode");
       QMenu *ResolutionSetting=SettingMenu->addMenu("Screen Resolution");





    //QAction *Res1 = new QAction ("&100X100",this);


    QAction *EditTimePrayers = new QAction ("&Edit Prayer Times",this);
    QAction *EditTimeIqamah = new QAction ("&Edit Iqamah Times",this);
    QAction *Time = new QAction("&Edit Hijri Date",this);
    QAction *Arabic = new QAction ("Arabic",this);
    QAction *English = new QAction ("English",this);
    QAction *BlackThema = new QAction("Black",this);
    QAction *WhiteThema = new QAction("White",this);
    QAction *FactoryReset = new QAction("Factory Reset",this);
    QAction *DefaultConfig = new QAction ("Default Configuration",this);
    QAction *AddMessage = new QAction ("Add Message", this);
    QAction *Mothen = new QAction ("Mothen", this);
    QAction *Fajer_azan = new QAction ("Enable Fajer", this);
    QAction *Dhuhr_azan = new QAction ("Enable Dhuhr", this);
    QAction *Asr_azan = new QAction ("Enable Asr", this);
    QAction *Magrib_azan= new QAction ("Enable Magrib", this);
    QAction *Isha_azan = new QAction ("Enable Isha", this);
    QAction *Sleep_Default=new QAction ("Default Mode", this);
    QAction *Sleep_None=new QAction ("Always Mode", this);
    QAction *wireless=SettingMenu->addAction("Connect to Wireless");
    QAction *database=SettingMenu->addAction("Sync Database");
    QAction *reboot=SettingMenu->addAction("Reboot");
    QAction *shutdown=SettingMenu->addAction("Shutdown");
    QAction *update=SettingMenu->addAction("Update");













    enum UPDATE{
        ALL,THEME,LANG,IQAMAH,DATE,PRAYER_METHOD,PRAYER_ADD,AZAN,SLEEP,VOLUME
    };


     QSqlQuery Query;

     QSize sizeofclock;
     QSize sizeofPrayer;
     QSize sizeofPrayerEdit;
     QSize sizeofIslamicEvent;
    QPushButton *SettingButton = new QPushButton(this);
    QPushButton *TimeEditButton = new QPushButton(this);
    QPushButton *HijriPlus = new QPushButton(this);
    QPushButton *HijriMinus = new QPushButton(this);
    QLabel      *HijriEditLabel = new QLabel(this);

    void SettingPushButtonWidget(QSize size , int SettingButtonPositionX, int SettingButtonPositionY );
    void PrayerEditPushButtonWidget(QSize size , int PrayerEditButtonPositionX, int PrayerEditButtonPositionY );
    //----->>> Setting Button and its Properties <<<---//
    void RefreshTimes(int UPDATE);
    void UpdateHadithQuranInterface();
    void sendMessage(QString msgToSend);
    void connectToHost(QString hostname, int port);
    virtual void mousePressEvent(QMouseEvent *event);
    QString getMacAddress();

private slots:
    void on_SaveMessage();
    void on_iqamahEditButton();
    void on_SettingButton();
    void on_PrayerTimeEditButton();
    void AdjustmentClockPlus();
    void AdjustmentClockMinus();
    void ActiveAdjustmentClock();
    void ActiveAdjustmentPrayer();
    void ActivePrayerMenu();
    void IncreaseTime(QString whichButton);
    void showTime();
    void iqamahMessage();
    void AnimationUp();
    void AnimationDown();
    void HadithQuran(int &XPosition,int &YPosition);
    void ChangeInterfaceLanguageArabic();
    void ChangeInterfaceLanguageEnglish();
    void ChangeInterfaceThemaBlack();
    void ChangeInterfaceThemaWhite();
    void ShowEditingHijriDate();
    void HijriPushButtonIncrease();
    void HijriPushButtonDecrease();
    void AddingMessageSlot();
    void DeletingSettingsFile();
    void DefaultSettings();
    void newConnection();
    void Store_Fajer_azan();
    void Store_Dhuhr_azan();
    void Store_Asr_azan();
    void Store_Magrib_azan();
    void Store_Isha_azan();
    void Store_Sleep_None();
    void Store_Sleep_Def();
    void onfinish(QNetworkReply *rep);
    void wirelss_function();
    void sync_database();
    void reboot_slot();
    void shutdown_slot();
    void OnResult(QNetworkReply *reply);
    void resolutionChange(QAction *action);
    void update_slot();
    //void AdjustmentClockMinus();

signals:
    void clicked1(QString text);


private:
    QString ApplicationPath=QCoreApplication::applicationDirPath();
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
