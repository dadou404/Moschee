#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include<QLabel>
#include<QRect>
#include<QPushButton>
#include<QComboBox>
#include<QMenu>
#include<QTime>
#include<QDate>
#include"hijri.h"
#include<QListView>
#include<QDebug>
#include<QObject>
#include<QTime>
#include<iostream>
#include<QSignalMapper>
#include"initlializationsettingfile.h"
#include<iostream>
#include<QPainter>
#include<QFont>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QKeyEvent>
#include<iostream>
#include <cstdlib>
#include"socket.h"
#include<QMediaPlayer>
#include<QSound>
#include<QUdpSocket>
#include<QNetworkReply>
#include<QNetworkInterface>
#include<QVariantMap>
#include<iostream>
#include<screeninformation.h>
#include <QProcess>
using namespace std;

QStringList lines;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    // Resolution Settings
    QString resolution="resolution.txt";
    QFile available_resolution (resolution);
    available_resolution.remove();
    system("xrandr |grep x |awk '{print $1}'>> resolution.txt");
    QFile file(resolution);
    if(!file.open(QIODevice::ReadOnly)) {
          qDebug()<<"Can not open the file";
     }

    QTextStream input(&file);

    while(!input.atEnd()) {
         QString line = input.readLine();
         lines.append(line);
     }

    QActionGroup *allAction = new QActionGroup(ResolutionSetting);

    for(int i=2;i<lines.size()-2;i++){
        //allResolution[i-2] = new QAction(lines[i],this);
        allAction->addAction(ResolutionSetting->addAction(lines[i]))->setData(i);
    }

   QObject::connect(allAction, SIGNAL(triggered(QAction*)), this, SLOT(resolutionChange(QAction*)));
   QObject::connect(update,SIGNAL(triggered()),this,SLOT(update_slot()));




//-------->>>
        enum	// long options missing a short form
                {
                    DHUHR_MINUTES = 9,
                    MAGHRIB_MINUTES,
                    ISHA_MINUTES,
                    FAJR_ANGLE,
                    MAGHRIB_ANGLE,
                    ISHA_ANGLE,
                };

        server = new QTcpServer(this);
            // whenever a user connects, it will emit signal
            connect(server, SIGNAL(newConnection()),
                    this, SLOT(newConnection()));
           // server1->setSocketOption(QAbstractSocket::KeepAliveOption,1);

            if(!server->listen(QHostAddress::Any, 44092))
            {
                qDebug() << "Server could not start";
            }
            else
            {
                qDebug() << "Server started!";
            }



         //test.readyRead();

            connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
              //  connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

        v_ArabicLang=Settings.ReadSettings("InterfaceLanguage","Arabic").toBool();
        ArabicLang=&v_ArabicLang;

       addedTimeFajer_v=Settings.ReadSettings("PrayerAdjustment","AddedTimeFajer").toInt();
       addedTimeShrouq_v=Settings.ReadSettings("PrayerAdjustment","AddedTimeShrouq").toInt();
       addedTimeDhuhr_v=Settings.ReadSettings("PrayerAdjustment","AddedTimeDhuhr").toInt();
       addedTimeAsr_v=Settings.ReadSettings("PrayerAdjustment","AddedTimeAsr").toInt();
       addedTimeMagrib_v=Settings.ReadSettings("PrayerAdjustment","AddedTimeMagrib").toInt();
       addedTimeIsha_v=Settings.ReadSettings("PrayerAdjustment","AddedTimeIsha").toInt();
       addedTimeAsr=&addedTimeAsr_v;
       addedTimeDhuhr=&addedTimeDhuhr_v;
       addedTimeFajer=&addedTimeFajer_v;
       addedTimeIsha=&addedTimeIsha_v;
       addedTimeMagrib=&addedTimeMagrib_v;
       addedTimeShrouq=&addedTimeShrouq_v;

       iqamahTimeFajer_v=Settings.ReadSettings("iqamahAdjustment","iqamahTimeFajer").toInt();
       iqamahTimeShrouq_v=Settings.ReadSettings("iqamahAdjustment","iqamahTimeShrouq").toInt();
       iqamahTimeDhuhr_v=Settings.ReadSettings("iqamahAdjustment","iqamahTimeDhuhr").toInt();
       iqamahTimeAsr_v=Settings.ReadSettings("iqamahAdjustment","iqamahTimeAsr").toInt();
       iqamahTimeMagrib_v=Settings.ReadSettings("iqamahAdjustment","iqamahTimeMagrib").toInt();
       iqamahTimeIsha_v=Settings.ReadSettings("iqamahAdjustment","iqamahTimeIsha").toInt();
       iqamahTimeAsr=&iqamahTimeAsr_v;
       iqamahTimeDhuhr=&iqamahTimeDhuhr_v;
       iqamahTimeFajer=&iqamahTimeFajer_v;
       iqamahTimeIsha=&iqamahTimeIsha_v;
       iqamahTimeMagrib=&iqamahTimeMagrib_v;
       iqamahTimeShrouq=&iqamahTimeShrouq_v;

       HijriAddedDays_v=Settings.ReadSettings("Hijri","AddedDays").toInt();
       HijriAddedDays=&HijriAddedDays_v;
       currentPrayerPtr=&currentPrayer;

     /* prayer_times.set_dhuhr_minutes(5);
        prayer_times.set_maghrib_minutes(0);
        prayer_times.set_isha_minutes(1);
        prayer_times.set_fajr_angle(18);
        prayer_times.set_maghrib_angle(17);
        prayer_times.set_isha_angle(5);*/
       prayerMethod= Settings.ReadSettings("PrayerSettings","Method").toString();
       QString AsrMethod= Settings.ReadSettings("PrayerSettings","AsrMethod").toString();

       if(prayerMethod=="University of Islamic Sciences")
           prayer_times.set_calc_method(PrayerTimes::Karachi);
        else if (prayerMethod=="Muslim World League (MWL)")
        prayer_times.set_calc_method(PrayerTimes::MWL);
       else if (prayerMethod=="Umm al-Qura University")
       prayer_times.set_calc_method(PrayerTimes::Makkah);
       else if (prayerMethod=="Egyptian General Authority of Survey")
       prayer_times.set_calc_method(PrayerTimes::Egypt);
       else if (prayerMethod=="Islamic Society of North America (ISNA)")
       prayer_times.set_calc_method(PrayerTimes::ISNA);
       else
           prayer_times.set_calc_method(PrayerTimes::Jafari);


       if(AsrMethod=="Standard")
        prayer_times.set_asr_method(PrayerTimes::Shafii);
       else
           prayer_times.set_asr_method(PrayerTimes::Hanafi);


        prayer_times.set_high_lats_adjust_method(PrayerTimes::None);


        enum CalculationMethod
        {
            Jafari, 	// Ithna Ashari
            Karachi,	// University of Islamic Sciences, Karachi
            ISNA,   	// Islamic Society of North America (ISNA)
            MWL,    	// Muslim World League (MWL)
            Makkah, 	// Umm al-Qura, Makkah
            Egypt,  	// Egyptian General Authority of Survey
            Custom, 	// Custom Setting

            CalculationMethodsCount
        };

        TimeEditButton->setVisible(false);
        ClockAdjustmentminus->setVisible(false);
        ClockAdjustmentplus->setVisible(false);
        ClockAdjustmentLabel->setVisible(false);
        PrayerFajerAdjustPlus->setVisible(false);
        PrayerFajerAdjustMinus->setVisible(false);
        PrayerSharouqAdjustPlus->setVisible(false);
        PrayerSharouqAdjustMinus->setVisible(false);
        PrayerDhuhrAdjustPlus->setVisible(false);
        PrayerDhuhrAdjustMinus->setVisible(false);
        PrayerAsrAdjustPlus->setVisible(false);
        PrayerAsrAdjustMinus->setVisible(false);
        PrayerMagribAdjustPlus->setVisible(false);
        PrayerMagribAdjustMinus->setVisible(false);
        PrayerIshaAdjustPlus->setVisible(false);
        PrayerIshaAdjustMinus->setVisible(false);
        FajerEditLabel->setVisible(false);
        ShrouqEditLabel->setVisible(false);
        DhuhrEditLabel->setVisible(false);
        AsrEditLabel->setVisible(false);
        MagribEditLabel->setVisible(false);
        IshaEditLabel->setVisible(false);
        HijriMinus->setVisible(false);
        HijriPlus->setVisible(false);
        HijriEditLabel->setVisible(false);
        HijriMinus->raise();
        HijriPlus->raise();
        ThemaChange=true;
        HadithQuranLabel->setWordWrap(true);
        //IslamicEventTitle->setWordWrap(true);



   //------------------------- Style Settings and Resolution------------------//
   //Two function for reading Css File and another function for reading the Screen Size
    // another function for changing the Background
    //----->> Classes instantation

    //--->> StyleSheet
       QString Thema = Settings.ReadSettings("appreance","Thema").toString();
    if(Thema=="Black"){
    CssFile=StyleSheetFile.ParsingCssFile(ApplicationPath+"/StyleSheet/BlackThema.css");
    this->setStyleSheet(StyleSheetFile.BackgroundChanging(ApplicationPath));
    }else {
        CssFile=StyleSheetFile.ParsingCssFile(ApplicationPath+"/StyleSheet/WhiteThema.css");
        this->setStyleSheet(StyleSheetFile.BackgroundChanging(ApplicationPath));

    }



    ScreenInformation screen;
    qDebug()<<"screen"<<screen.ScreenSize().width()/2<<screen.ScreenSize().height()/2;
    progress->setGeometry(QRect((screen.ScreenSize().width()/2)-100,(screen.ScreenSize().height()/2)-50,200,100));
    progress->setProperty("Type",1);
    progress->style()->polish(this);
    progress->style()->unpolish(this);
    progress->setStyleSheet(CssFile);
    progress->setText("Progress");
    progress->hide();
    //--->> Sizes of widgets and resolution value <<----//

    QSize  ScreenSize=Screen.ScreenSize();
     sizeofclock=QSize(300,400);
    // sizeofPrayer=QSize(200,50);
     sizeofPrayerEdit=QSize(250,50);
     sizeofIslamicEvent=QSize(40,400);
    //--->> Widegts


   int PrayerWidgetPositionSpace=10;

    PrayerWidget(sizeofPrayer,PrayerWidgetPosition[0],PrayerWidgetPosition[1],PrayerWidgetPositionSpace, *ArabicLang);
    ClockWidget(sizeofclock,ClockPosition[0],ClockPosition[1]);
    PrayerEdit(sizeofPrayerEdit,0,0);
    TodayIslamicEvent(sizeofIslamicEvent,20,325);
    int addedDayHijri=Settings.ReadSettings("Hijri","AddedDays").toInt();
    ClockLabel->setText(QTime::currentTime().toString("hh:mm"));
    int day = QDate::currentDate().day();
    int month = QDate::currentDate().month();
    int year = QDate::currentDate().year();
    QString date = HijriDate.PrintCalender(day+addedDayHijri,month,year,0);
    HijriLabel->setText(date);

    GregorianLabel->setText(QDate::currentDate().toString("yyyy-MMMM-dd"));
    v_ArabicLang=Settings.ReadSettings("InterfaceLanguage","Arabic").toBool();
    a_fajer=Settings.ReadSettings("Azan","fajer").toBool();
    a_dhuhr=Settings.ReadSettings("Azan","dhuhr").toBool();
    a_asr=Settings.ReadSettings("Azan","asr").toBool();
    a_mgrib=Settings.ReadSettings("Azan","magrib").toBool();
    a_isha=Settings.ReadSettings("Azan","isha").toBool();

    //---->> Signals and Slots <<----//


    QObject::connect(SettingButton,SIGNAL(clicked()),this,SLOT(on_SettingButton()));
    QObject::connect(ClockAdjustmentplus,SIGNAL(clicked()),this,SLOT(AdjustmentClockPlus()));
    QObject::connect(ClockAdjustmentminus,SIGNAL(clicked()),this,SLOT(AdjustmentClockMinus()));
    //QObject::connect(PrayerEditButton,SIGNAL(clicked()),this,SLOT(ActiveAdjustmentPrayer()));
    QObject::connect(EditTimePrayers,SIGNAL(triggered()),this,SLOT(ActiveAdjustmentPrayer()));
    QObject::connect(TimeEditButton,SIGNAL(clicked()),this,SLOT(ActiveAdjustmentClock()));
    QObject::connect(EditTimeIqamah,SIGNAL(triggered()),this,SLOT(on_iqamahEditButton()));
    QObject::connect(Arabic,SIGNAL(triggered()),this,SLOT(ChangeInterfaceLanguageArabic()));
    QObject::connect(English,SIGNAL(triggered()),this,SLOT(ChangeInterfaceLanguageEnglish()));
    QObject::connect(BlackThema,SIGNAL(triggered()),this,SLOT(ChangeInterfaceThemaBlack()));
    QObject::connect(WhiteThema,SIGNAL(triggered()),this,SLOT(ChangeInterfaceThemaWhite()));
    QObject::connect(AddMessage,SIGNAL(triggered()),this,SLOT(AddingMessageSlot()));
    QObject::connect(FactoryReset,SIGNAL(triggered()),this,SLOT(DeletingSettingsFile()));
    QObject::connect(DefaultConfig,SIGNAL(triggered()),this,SLOT(DefaultSettings()));
    QObject::connect(Time,SIGNAL(triggered()),this,SLOT(ShowEditingHijriDate()));
    QObject::connect(HijriPlus,SIGNAL(clicked()),this,SLOT(HijriPushButtonIncrease()));
    QObject::connect(HijriMinus,SIGNAL(clicked()),this,SLOT(HijriPushButtonDecrease()));
    QObject::connect(SaveMessage,SIGNAL(clicked()),this,SLOT(on_SaveMessage()));
    QObject::connect(Fajer_azan,SIGNAL(triggered()),this,SLOT(Store_Fajer_azan()));
    QObject::connect(Dhuhr_azan,SIGNAL(triggered()),this,SLOT(Store_Dhuhr_azan()));
    QObject::connect(Asr_azan,SIGNAL(triggered()),this,SLOT(Store_Asr_azan()));
    QObject::connect(Magrib_azan,SIGNAL(triggered()),this,SLOT(Store_Magrib_azan()));
    QObject::connect(Isha_azan,SIGNAL(triggered()),this,SLOT(Store_Isha_azan()));
    QObject::connect(Sleep_None,SIGNAL(triggered()),this,SLOT(Store_Sleep_None()));
    QObject::connect(Sleep_Default,SIGNAL(triggered()),this,SLOT(Store_Sleep_Def()));
    QObject::connect(wireless,SIGNAL(triggered()),this,SLOT(wirelss_function()));
    QObject::connect(database,SIGNAL(triggered()),this,SLOT(sync_database()));
    QObject::connect(reboot,SIGNAL(triggered()),this,SLOT(reboot_slot()));
    QObject::connect(shutdown,SIGNAL(triggered()),this,SLOT(shutdown_slot()));















       QSignalMapper *signalMapper = new QSignalMapper(this);

    QObject::connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(IncreaseTime(QString)));
    signalMapper->setMapping(PrayerFajerAdjustPlus, "InFajer" );
    signalMapper->setMapping(PrayerFajerAdjustMinus, "DecFajer" );
    signalMapper->setMapping(PrayerSharouqAdjustPlus, "InShrouq" );
    signalMapper->setMapping(PrayerSharouqAdjustMinus, "DecShrouq" );
    signalMapper->setMapping(PrayerDhuhrAdjustPlus, "InDhuhr" );
    signalMapper->setMapping(PrayerDhuhrAdjustMinus, "DecDhuhr" );
    signalMapper->setMapping(PrayerAsrAdjustPlus, "InAsr" );
    signalMapper->setMapping(PrayerAsrAdjustMinus, "DecAsr" );
    signalMapper->setMapping(PrayerMagribAdjustPlus, "InMagrib" );
    signalMapper->setMapping(PrayerMagribAdjustMinus, "DecMagrib" );
    signalMapper->setMapping(PrayerIshaAdjustPlus, "InIsha" );
    signalMapper->setMapping(PrayerIshaAdjustMinus, "DecIsha" );
    QObject::connect(PrayerFajerAdjustPlus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerFajerAdjustMinus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerSharouqAdjustPlus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerSharouqAdjustMinus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerDhuhrAdjustPlus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerDhuhrAdjustMinus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerAsrAdjustPlus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerAsrAdjustMinus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerMagribAdjustPlus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerMagribAdjustMinus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerIshaAdjustPlus, SIGNAL(clicked()), signalMapper, SLOT(map()));
    QObject::connect(PrayerIshaAdjustMinus, SIGNAL(clicked()), signalMapper, SLOT(map()));




    QObject::connect(timer, SIGNAL(timeout()),this,SLOT(showTime()));
         timer->start(1000);
    QObject::connect(timer1, SIGNAL(timeout()),this,SLOT(AnimationUp()));
    QObject::connect(timer2, SIGNAL(timeout()),this,SLOT(AnimationDown()));
    QObject::connect(iqamahTimer,SIGNAL(timeout()),this,SLOT(iqamahMessage()));


    //---->> Signals and Slots <<----//


    SettingButton->raise();
    SettingButton->setText("Settings");
    SaveMessage->setVisible(false);
    /*
    PrayerTimeEditButton->setText("Prayers Edit");
    PrayerTimeEditButton->raise();
    PrayerEditButton->setText("Prayer Edit");
    PrayerEditButton->raise();
    iqamahEditButton->setText("Iqamah Time");
    iqamahEditButton->raise();
    TimeEditButton->setText("Time Edit");
    TimeEditButton->raise();
    */
   //---------------->> Visibility of Editing Time and Prayers items




    int Clock_X_Position=Settings.ReadSettings("Position","Clock_x").toInt();
    int Clock_Y_Position=Settings.ReadSettings("Position","Clock_y").toInt();
    int Prayer_X_Widget_Position=Settings.ReadSettings("Position","Prayer_X_W_Position").toInt();
    int Prayer_Y_Widget_Position=Settings.ReadSettings("Position","Prayer_Y_W_Position").toInt();
    ClockPosition[0]=Clock_X_Position;
    ClockPosition[1]=Clock_Y_Position;
    PrayerWidgetPosition[0]=Prayer_X_Widget_Position;
    PrayerWidgetPosition[1]=Prayer_Y_Widget_Position;

            AddingMessageMenu->addAction(AddMessage);
            FactoryResetMenu->addAction(FactoryReset);
            FactoryResetMenu->addAction(DefaultConfig);
            PrayersMenu->addAction(EditTimePrayers);
            PrayersMenu->addAction(EditTimeIqamah);
            TimeMenu->addAction(Time);
            Language->addAction(Arabic);
            Language->addAction(English);
            InterfaceThema->addAction(BlackThema);
            InterfaceThema->addAction(WhiteThema);
            Sleeping_Mode->addAction(Sleep_Default);
            Sleeping_Mode->addAction(Sleep_None);
            //Fajer_azan->setActionGroup(m_actionGroup);

            AzanSettings_azan->addAction(Fajer_azan);
            AzanSettings_azan->addAction(Dhuhr_azan);
            AzanSettings_azan->addAction(Asr_azan);
            AzanSettings_azan->addAction(Magrib_azan);
            AzanSettings_azan->addAction(Isha_azan);
            Fajer_azan->setCheckable(true);
            Dhuhr_azan->setCheckable(true);
            Asr_azan->setCheckable(true);
            Magrib_azan->setCheckable(true);
            Isha_azan->setCheckable(true);
            Sleep_Default->setCheckable(true);
            Sleep_None->setCheckable(true);


    AddingMessageEvent->setVisible(false);

     SettingMenu->setProperty("Type",15);
     SettingMenu->style()->polish(this);
     SettingMenu->style()->unpolish(this);
     SettingMenu->setStyleSheet(CssFile);
     PrayersMenu->setProperty("Type",15);
     PrayersMenu->style()->polish(this);
     PrayersMenu->style()->unpolish(this);
     PrayersMenu->setStyleSheet(CssFile);
     TimeMenu->setProperty("Type",15);
     TimeMenu->style()->polish(this);
     TimeMenu->style()->unpolish(this);
     TimeMenu->setStyleSheet(CssFile);
     Language->setProperty("Type",15);
     Language->style()->polish(this);
     Language->style()->unpolish(this);
     Language->setStyleSheet(CssFile);
     InterfaceThema->setProperty("Type",15);
     InterfaceThema->style()->polish(this);
     InterfaceThema->style()->unpolish(this);
     InterfaceThema->setStyleSheet(CssFile);
     FactoryResetMenu->setProperty("Type",15);
     FactoryResetMenu->style()->polish(this);
     FactoryResetMenu->style()->unpolish(this);
     FactoryResetMenu->setStyleSheet(CssFile);
     AddingMessageMenu->setProperty("Type",15);
     AddingMessageMenu->style()->polish(this);
     AddingMessageMenu->style()->unpolish(this);
     AddingMessageMenu->setStyleSheet(CssFile);
     AzanSettings_azan->setProperty("Type",15);
     AzanSettings_azan->style()->polish(this);
     AzanSettings_azan->style()->unpolish(this);
     AzanSettings_azan->setStyleSheet(CssFile);
     AzanSettings_Mothen->setProperty("Type",15);
     AzanSettings_Mothen->style()->polish(this);
     AzanSettings_Mothen->style()->unpolish(this);
     AzanSettings_Mothen->setStyleSheet(CssFile);

             AzanSettings->setProperty("Type",15);
             AzanSettings->style()->polish(this);
             AzanSettings->style()->unpolish(this);
             AzanSettings->setStyleSheet(CssFile);

             Sleeping_Mode->setProperty("Type",15);
             Sleeping_Mode->style()->polish(this);
             Sleeping_Mode->style()->unpolish(this);
             Sleeping_Mode->setStyleSheet(CssFile);

    /* QMenu *AzanSettings_azan = AzanSettings->addMenu("Prayer Settings");
     QMenu *AzanSettings_Mothen = AzanSettings->addMenu("Moethn Settings");



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
  QAction *Isha_azan = new QAction ("Add Message", this);
     */


 //    SettingMenu->addAction(Prayers);

      SettingButton->setMenu(SettingMenu);
   //   QObject::connect(&EditTimePrayers,SIGNAL(triggered()),this,SLOT(on_iqamahEditButton()));


    //qDebug()<<addedTimeFajer<<addedTimeShrouq<<addedTimeDhuhr<<addedTimeAsr<<addedTimeMagrib<<addedTimeIsha;
    //-----------------------------------------------------------------------//

    //----->> Animation
    iqamahMessageLabel->setGeometry(QRect(0,ScreenSize.height(),1000,ScreenSize.width()));
    iqamahMessageLabel->setProperty("Type",0);
    iqamahMessageLabel->style()->polish(this);
    iqamahMessageLabel->style()->unpolish(this);
    iqamahMessageLabel->setStyleSheet(CssFile);
    iqamahMessageLabel->raise();
    //iqamahMessageLabel->setText("حان موعد اذان صلاة الفجر");
    iqamahMessageLabel->show();

    TimeEditButton->setVisible(false);
    ClockAdjustmentminus->setVisible(false);
    ClockAdjustmentplus->setVisible(false);
    ClockAdjustmentLabel->setVisible(false);
    PrayerFajerAdjustPlus->setVisible(false);
    PrayerFajerAdjustMinus->setVisible(false);
    PrayerSharouqAdjustPlus->setVisible(false);
    PrayerSharouqAdjustMinus->setVisible(false);
    PrayerDhuhrAdjustPlus->setVisible(false);
    PrayerDhuhrAdjustMinus->setVisible(false);
    PrayerAsrAdjustPlus->setVisible(false);
    PrayerAsrAdjustMinus->setVisible(false);
    PrayerMagribAdjustPlus->setVisible(false);
    PrayerMagribAdjustMinus->setVisible(false);
    PrayerIshaAdjustPlus->setVisible(false);
    PrayerIshaAdjustMinus->setVisible(false);
    FajerEditLabel->setVisible(false);
    ShrouqEditLabel->setVisible(false);
    DhuhrEditLabel->setVisible(false);
    AsrEditLabel->setVisible(false);
    MagribEditLabel->setVisible(false);
    IshaEditLabel->setVisible(false);
    HijriEditLabel->setVisible(false);
    HijriMinus->setVisible(false);
    HijriPlus->setVisible(false);
    HijriMinus->raise();
    HijriPlus->raise();

    RefreshTimes(UPDATE::ALL);
    UpdateHadithQuranInterface();



  }


//------------- clock Position and its Properties ----------------------
void MainWindow::ClockWidget(QSize size, int ClockPositionX, int ClockPositionY){
    ClockLabel->setGeometry(QRect(ClockPositionX,ClockPositionY,size.height(),size.width()));
    ClockLabel->setProperty("Type",3);
    ClockLabel->style()->polish(this);
    ClockLabel->style()->unpolish(this);
    ClockLabel->setAlignment(Qt::AlignTop);
    ClockLabel->setAlignment(Qt::AlignHCenter);
    ClockLabel->setStyleSheet(CssFile);
    ClockLabel->show();

    ClockAdjustmentplus->setGeometry(QRect(ClockPositionX+size.height(),ClockPositionY,50,50));
    ClockAdjustmentplus->setText("++");
    ClockAdjustmentplus->setProperty("Type",16);
    ClockAdjustmentplus->style()->polish(this);
    ClockAdjustmentplus->style()->unpolish(this);
    ClockAdjustmentplus->raise();
 //   ClockAdjustmentplus->setAlignment(Qt::AlignLeft);
    ClockAdjustmentplus->setStyleSheet(CssFile);
    ClockAdjustmentplus->show();
ClockAdjustmentplus->setVisible(false);

    ClockAdjustmentLabel->setGeometry(QRect(ClockPositionX+size.height(),ClockAdjustmentplus->pos().y()+50,100,50));
    ClockAdjustmentLabel->setText("--");
    ClockAdjustmentLabel->setProperty("Type",1);
    ClockAdjustmentLabel->style()->polish(this);
    ClockAdjustmentLabel->style()->unpolish(this);
    ClockAdjustmentLabel->raise();
  //  ClockAdjustmentminus->setAlignment(Qt::AlignLeft);
    ClockAdjustmentLabel->setStyleSheet(CssFile);
    ClockAdjustmentLabel->show();
    ClockAdjustmentLabel->setVisible(false);

    ClockAdjustmentminus->setGeometry(QRect(ClockPositionX+size.height(),ClockAdjustmentplus->pos().y()+100,50,50));
    ClockAdjustmentminus->setText("-");
    ClockAdjustmentminus->setProperty("Type",16);
    ClockAdjustmentminus->style()->polish(this);
    ClockAdjustmentminus->style()->unpolish(this);
    ClockAdjustmentminus->raise();
  //  ClockAdjustmentminus->setAlignment(Qt::AlignLeft);
    ClockAdjustmentminus->setStyleSheet(CssFile);
    ClockAdjustmentminus->show();
    ClockAdjustmentminus->setVisible(false);

    HijriLabel->setGeometry(QRect(ClockPositionX,ClockPositionY,400,400));
    HijriLabel->setProperty("Type",4);
    HijriLabel->style()->polish(this);
    HijriLabel->style()->unpolish(this);
    HijriLabel->setAlignment(Qt::AlignCenter);
    HijriLabel->setStyleSheet(CssFile);
    HijriLabel->show();
    if(*ArabicLang){
    HijriPlus->setGeometry(QRect(ClockPositionX+ClockLabel->geometry().width()+205,HijriLabel->geometry().y()+180,50,50));
    HijriPlus->setProperty("Type",16);
    HijriPlus->style()->polish(this);
    HijriPlus->style()->unpolish(this);
    HijriPlus->setStyleSheet(CssFile);
    HijriPlus->setText("+");
    HijriPlus->show();

    HijriEditLabel->setGeometry(QRect(ClockPositionX+ClockLabel->geometry().width()+5,HijriLabel->geometry().y()+180,250,50));
    HijriEditLabel->setProperty("Type",1);
    HijriEditLabel->style()->polish(this);
    HijriEditLabel->style()->unpolish(this);
    HijriEditLabel->setStyleSheet(CssFile);
    HijriEditLabel->setText(QString::number(*HijriAddedDays));
    HijriEditLabel->show();


    HijriMinus->setGeometry(QRect(ClockPositionX+ClockLabel->geometry().width()+5,HijriLabel->geometry().y()+180,50,50));
    HijriMinus->setProperty("Type",16);
    HijriMinus->style()->polish(this);
    HijriMinus->style()->unpolish(this);
    HijriMinus->setStyleSheet(CssFile);
    HijriMinus->setText("-");
    HijriMinus->show();
}else{

        HijriPlus->setGeometry(QRect(HijriLabel->geometry().x()-HijriLabel->width(), HijriLabel->geometry().y()+(ClockLabel->height()/2),50,50));
        HijriPlus->setProperty("Type",16);
        HijriPlus->style()->polish(this);
        HijriPlus->style()->unpolish(this);
        HijriPlus->setStyleSheet(CssFile);
        HijriPlus->setText("+");
        HijriPlus->show();

        HijriEditLabel->setGeometry(QRect(HijriLabel->geometry().x()-HijriLabel->width(), HijriLabel->geometry().y()+(ClockLabel->height()/2),250,50));
        HijriEditLabel->setProperty("Type",1);
        HijriEditLabel->style()->polish(this);
        HijriEditLabel->style()->unpolish(this);
        HijriEditLabel->setStyleSheet(CssFile);
        HijriEditLabel->setText(QString::number(*HijriAddedDays));
        HijriEditLabel->show();


        HijriMinus->setGeometry(QRect(HijriLabel->geometry().x()-HijriLabel->width()+HijriEditLabel->width()-50, HijriLabel->geometry().y()+(ClockLabel->height()/2),50,50));
        HijriMinus->setProperty("Type",16);
        HijriMinus->style()->polish(this);
        HijriMinus->style()->unpolish(this);
        HijriMinus->setStyleSheet(CssFile);
        HijriMinus->setText("-");
        HijriMinus->show();


    }

    GregorianLabel->setGeometry(QRect(ClockPositionX,ClockPositionY+40,400,400));
    GregorianLabel->setProperty("Type",4);
    GregorianLabel->style()->polish(this);
    GregorianLabel->style()->unpolish(this);
    GregorianLabel->setAlignment(Qt::AlignCenter);
    GregorianLabel->setStyleSheet(CssFile);
    GregorianLabel->show();


}
void MainWindow::PrayerWidget(QSize size, int PrayerPositionX, int PrayerPositionY, int VSpacing, bool &ArabicLang){

    FajerLabel->setGeometry(QRect(PrayerPositionX,PrayerPositionY,size.width(),size.height()));
    FajerLabel->setProperty("Type",2);
    FajerLabel->style()->polish(this);
    FajerLabel->style()->unpolish(this);
    FajerLabel->setStyleSheet(CssFile);
    FajerLabel->show();
    if(ArabicLang==true){
        FajerTimeLabel->setGeometry(QRect(PrayerPositionX-size.width()-5,PrayerPositionY,size.width(),size.height()));
        FajerLabel->setText("فجر");

    }else
    {
        FajerTimeLabel->setGeometry(QRect(PrayerPositionX+size.width()+5,PrayerPositionY,size.width(),size.height()));
        FajerLabel->setText("Fajer");

    }
    FajerTimeLabel->setProperty("Type",1);
    FajerTimeLabel->style()->polish(this);
    FajerTimeLabel->style()->unpolish(this);
    FajerTimeLabel->setStyleSheet(CssFile);
    //FajerTimeLabel->setText("Hello");
    FajerTimeLabel->show();


    SharouqLabel->setGeometry(QRect(PrayerPositionX,PrayerPositionY+size.height()+VSpacing,size.width(),size.height()));
    SharouqLabel->setProperty("Type",2);
    SharouqLabel->style()->polish(this);
    SharouqLabel->style()->unpolish(this);
    SharouqLabel->setStyleSheet(CssFile);

    SharouqLabel->show();
    if(ArabicLang==true){
       SharouqTimeLabel->setGeometry(QRect(PrayerPositionX-size.width()-5,PrayerPositionY+size.height()+VSpacing,size.width(),size.height()));
        SharouqLabel->setText("شروق");
    }else
    {
       SharouqTimeLabel->setGeometry(QRect(PrayerPositionX+size.width()+5,PrayerPositionY+size.height()+VSpacing,size.width(),size.height()));
        SharouqLabel->setText("Sharouq ");
    }
    SharouqTimeLabel->setProperty("Type",1);
    SharouqTimeLabel->style()->polish(this);
    SharouqTimeLabel->style()->unpolish(this);
    SharouqTimeLabel->setStyleSheet(CssFile);
    //SharouqTimeLabel->setText("Sharouq");
    SharouqTimeLabel->show();

    DhuhrLabel->setGeometry(QRect(PrayerPositionX,PrayerPositionY+2*size.height()+2*VSpacing,size.width(),size.height()));
    DhuhrLabel->setProperty("Type",2);
    DhuhrLabel->style()->polish(this);
    DhuhrLabel->style()->unpolish(this);
    DhuhrLabel->setStyleSheet(CssFile);
    DhuhrLabel->show();
    if(ArabicLang==true){
       DhuhrTimeLabel->setGeometry(QRect(PrayerPositionX-size.width()-5,PrayerPositionY+2*size.height()+2*VSpacing,size.width(),size.height()));
       if(QDate::currentDate().dayOfWeek()==5)
       DhuhrLabel->setText("الجمعة");
       else
       DhuhrLabel->setText("الظهر");


    }else
    {
       DhuhrTimeLabel->setGeometry(QRect(PrayerPositionX+size.width()+5,PrayerPositionY+2*size.height()+2*VSpacing,size.width(),size.height()));
       if(QDate::currentDate().dayOfWeek()==5)
       DhuhrLabel->setText("Jumma");
       else
       DhuhrLabel->setText("Dhuhr");

    }
    DhuhrTimeLabel->setProperty("Type",1);
    DhuhrTimeLabel->style()->polish(this);
    DhuhrTimeLabel->style()->unpolish(this);
    DhuhrTimeLabel->setStyleSheet(CssFile);
   // DhuhrTimeLabel->setText("Dhuhr");
    DhuhrTimeLabel->show();


    AsrLabel->setGeometry(QRect(PrayerPositionX,PrayerPositionY+3*size.height()+3*VSpacing,size.width(),size.height()));
    AsrLabel->setProperty("Type",2);
    AsrLabel->style()->polish(this);
    AsrLabel->style()->unpolish(this);
    AsrLabel->setStyleSheet(CssFile);
    AsrLabel->show();
    if(ArabicLang==true){
       AsrTimeLabel->setGeometry(QRect(PrayerPositionX-size.width()-5,PrayerPositionY+3*size.height()+3*VSpacing,size.width(),size.height()));
       AsrLabel->setText("عصر");

    }else
    {
       AsrTimeLabel->setGeometry(QRect(PrayerPositionX+size.width()+5,PrayerPositionY+3*size.height()+3*VSpacing,size.width(),size.height()));
       AsrLabel->setText("Asr");

    }
    AsrTimeLabel->setProperty("Type",1);
    AsrTimeLabel->style()->polish(this);
    AsrTimeLabel->style()->unpolish(this);
    AsrTimeLabel->setStyleSheet(CssFile);
    //AsrTimeLabel->setText("Asr");
    AsrTimeLabel->show();

    MagribLabel->setGeometry(QRect(PrayerPositionX,PrayerPositionY+4*size.height()+4*VSpacing,size.width(),size.height()));
    MagribLabel->setProperty("Type",2);
    MagribLabel->style()->polish(this);
    MagribLabel->style()->unpolish(this);
    MagribLabel->setStyleSheet(CssFile);
    MagribLabel->show();
   if(ArabicLang==true){
      MagribTimeLabel->setGeometry(QRect(PrayerPositionX-size.width()-5,PrayerPositionY+4*size.height()+4*VSpacing,size.width(),size.height()));
      MagribLabel->setText("مغرب");

    }else
    {
       MagribTimeLabel->setGeometry(QRect(PrayerPositionX+size.width()+5,PrayerPositionY+4*size.height()+4*VSpacing,size.width(),size.height()));
       MagribLabel->setText("Magrib");

    }
    MagribTimeLabel->setProperty("Type",1);
    MagribTimeLabel->style()->polish(this);
    MagribTimeLabel->style()->unpolish(this);
    MagribTimeLabel->setStyleSheet(CssFile);
    //MagribTimeLabel->setText("Asr");
    MagribTimeLabel->show();


    IshaLabel->setGeometry(QRect(PrayerPositionX,PrayerPositionY+5*size.height()+5*VSpacing,size.width(),size.height()));
    IshaLabel->setProperty("Type",2);
    IshaLabel->style()->polish(this);
    IshaLabel->style()->unpolish(this);
    IshaLabel->setStyleSheet(CssFile);

    IshaLabel->show();
    if(ArabicLang==true){
       IshaTimeLabel->setGeometry(QRect(PrayerPositionX-size.width()-5,PrayerPositionY+5*size.height()+5*VSpacing,size.width(),size.height()));
        IshaLabel->setText("عشاء");
    }else
    {
       IshaTimeLabel->setGeometry(QRect(PrayerPositionX+size.width()+5,PrayerPositionY+5*size.height()+5*VSpacing,size.width(),size.height()));
        IshaLabel->setText("Isha");
    }
    IshaTimeLabel->setProperty("Type",1);
    IshaTimeLabel->style()->polish(this);
    IshaTimeLabel->style()->unpolish(this);
    IshaTimeLabel->setStyleSheet(CssFile);
    //IshaTimeLabel->setText("Asr");
    IshaTimeLabel->show();




}
//------------- Settings Button Properties and its Position ---------------
void MainWindow::SettingPushButtonWidget(QSize size, int SettingButtonPositionX, int SettingButtonPositionY){

    SettingButton->setGeometry(QRect(0,SettingButtonPositionY-size.width(),size.height()+20,size.width()));
    SettingButton->setProperty("Type",15);
    SettingButton->style()->polish(this);
    SettingButton->style()->unpolish(this);
    SettingButton->setStyleSheet(CssFile);

  /*  PrayerTimeEditButton->setGeometry(QRect(0,SettingButtonPositionY-(size.width()*2),size.height()+20,size.width()));
    PrayerTimeEditButton->setProperty("Type",15);
    PrayerTimeEditButton->style()->polish(this);
    PrayerTimeEditButton->style()->unpolish(this);
    PrayerTimeEditButton->setStyleSheet(CssFile);

    TimeEditButton->setGeometry(QRect(0,SettingButtonPositionY-(size.width()*3),size.height()+20,size.width()));
    TimeEditButton->setProperty("Type",15);
    TimeEditButton->style()->polish(this);
    TimeEditButton->style()->unpolish(this);
    TimeEditButton->setStyleSheet(CssFile);
    TimeEditButton->show();
    */
}
void MainWindow::PrayerEditPushButtonWidget(QSize size, int PrayerEditButtonPositionX, int PrayerEditButtonPositionY){

/*    PrayerEditButton->setGeometry(QRect(PrayerTimeEditButton->geometry().x()+PrayerTimeEditButton->geometry().width()+2,PrayerTimeEditButton->geometry().y(),size.height()+20,size.width()));
    PrayerEditButton->setProperty("Type",15);
    PrayerEditButton->style()->polish(this);
    PrayerEditButton->style()->unpolish(this);
    PrayerEditButton->setStyleSheet(CssFile);

    iqamahEditButton->setGeometry(QRect(PrayerEditButton->geometry().x()+PrayerEditButton->geometry().width()+2,PrayerEditButton->geometry().y(),size.height()+20,size.width()));
    iqamahEditButton->setProperty("Type",15);
    iqamahEditButton->style()->polish(this);
    iqamahEditButton->style()->unpolish(this);
    iqamahEditButton->setStyleSheet(CssFile);
    */

}
//------------------ Settings Button Event connected with Signal above --------
void MainWindow::on_SettingButton(){
    visiblity=!visiblity;
   // PrayerTimeEditButton->setVisible(visiblity);
    //TimeEditButton->setVisible(visiblity);
   // PrayerEditButton->setVisible(false);
   // iqamahEditButton->setVisible(false);
}
void MainWindow::on_PrayerTimeEditButton(){
    PrayerEditVisible=!PrayerEditVisible;
   // PrayerEditButton->setVisible(PrayerEditVisible);
 //iqamahEditButton->setVisible(PrayerEditVisible);

}
void MainWindow::on_iqamahEditButton(){

    iqamahActive=!iqamahActive ;
    PrayerTimeVisible=false;
    PrayerFajerAdjustPlus->setVisible(iqamahActive);
    PrayerFajerAdjustMinus->setVisible(iqamahActive);
    PrayerSharouqAdjustPlus->setVisible(iqamahActive);
    PrayerSharouqAdjustMinus->setVisible(iqamahActive);
    PrayerDhuhrAdjustPlus->setVisible(iqamahActive);
    PrayerDhuhrAdjustMinus->setVisible(iqamahActive);
    PrayerAsrAdjustPlus->setVisible(iqamahActive);
    PrayerAsrAdjustMinus->setVisible(iqamahActive);
    PrayerMagribAdjustPlus->setVisible(iqamahActive);
    PrayerMagribAdjustMinus->setVisible(iqamahActive);
    PrayerIshaAdjustPlus->setVisible(iqamahActive);
    PrayerIshaAdjustMinus->setVisible(iqamahActive);
    FajerEditLabel->setVisible(iqamahActive);
    ShrouqEditLabel->setVisible(iqamahActive);
    DhuhrEditLabel->setVisible(iqamahActive);
    AsrEditLabel->setVisible(iqamahActive);
    MagribEditLabel->setVisible(iqamahActive);
    IshaEditLabel->setVisible(iqamahActive);
    FajerEditLabel->setText(QVariant(*iqamahTimeFajer).toString());
    ShrouqEditLabel->setText(QVariant(*iqamahTimeShrouq).toString());
    DhuhrEditLabel->setText(QVariant(*iqamahTimeDhuhr).toString());
    AsrEditLabel->setText(QVariant(*iqamahTimeAsr).toString());
    MagribEditLabel->setText(QVariant(*iqamahTimeMagrib).toString());
    IshaEditLabel->setText(QVariant(*iqamahTimeIsha).toString());



}
void MainWindow::TodayIslamicEvent(QSize size, int EventPositionX, int EventPositionY){

    IslamicEventTitle->setGeometry(QRect(EventPositionX,EventPositionY,size.height(),size.width()));
    IslamicEventTitle->setProperty("Type",2);
    IslamicEventTitle->style()->polish(this);
    IslamicEventTitle->style()->unpolish(this);
   // IslamicEventTitle->setAlignment(Qt::AlignVCenter);
    IslamicEventTitle->setAlignment(Qt::AlignTop);
    IslamicEventTitle->setAlignment(Qt::AlignCenter);
  // IslamicEventTitle->setText("Hello World how   ");
    IslamicEventTitle->setStyleSheet(CssFile);
    IslamicEventTitle->show();

    IslamicEventContent->setGeometry(QRect(EventPositionX,EventPositionY+size.width()+5,size.height(),size.width()+300));
    IslamicEventContent->setProperty("Type",14);
    IslamicEventContent->setWordWrap(true);
    IslamicEventContent->style()->polish(this);
    IslamicEventContent->style()->unpolish(this);
    IslamicEventContent->setAlignment(Qt::AlignTop);
    IslamicEventContent->setAlignment(Qt::AlignHCenter);
    //IslamicEventContent->setText("Hello World how are you fine sdflkaskdjm,adfklaeiof");
    IslamicEventContent->setStyleSheet(CssFile);
    IslamicEventContent->show();



}
void MainWindow::AdjustmentClockPlus(){
    indexplus=indexplus+1;
    plus=60*indexplus;
    ClockAdjustmentLabel->setText(QVariant(indexplus).toString());
    ClockLabel->setText(t.addSecs(plus).toString("hh:mm"));
    qDebug()<<t.toString("hh:mm")<<plus<<indexplus;
}
void MainWindow::AdjustmentClockMinus(){
    indexminus=indexminus+1;
    minus=-60*indexminus;
    ClockAdjustmentLabel->setText(QVariant(indexminus).toString());

    ClockLabel->setText(t.addSecs(minus).toString("hh:mm"));
    qDebug()<<t.toString("hh:mm")<<plus<<indexminus;
}
void MainWindow::ActiveAdjustmentClock(){

    ClockEditVisible=!ClockEditVisible;
    ClockAdjustmentplus->setVisible(ClockEditVisible);
    ClockAdjustmentminus->setVisible(ClockEditVisible);
    ClockAdjustmentLabel->setVisible(ClockEditVisible);
}
void MainWindow::ActiveAdjustmentPrayer(){
    PrayerTimeVisible= !PrayerTimeVisible;
    iqamahActive=false;

    PrayerFajerAdjustPlus->setVisible(PrayerTimeVisible);
    PrayerFajerAdjustMinus->setVisible(PrayerTimeVisible);
    PrayerSharouqAdjustPlus->setVisible(PrayerTimeVisible);
    PrayerSharouqAdjustMinus->setVisible(PrayerTimeVisible);
    PrayerDhuhrAdjustPlus->setVisible(PrayerTimeVisible);
    PrayerDhuhrAdjustMinus->setVisible(PrayerTimeVisible);
    PrayerAsrAdjustPlus->setVisible(PrayerTimeVisible);
    PrayerAsrAdjustMinus->setVisible(PrayerTimeVisible);
    PrayerMagribAdjustPlus->setVisible(PrayerTimeVisible);
    PrayerMagribAdjustMinus->setVisible(PrayerTimeVisible);
    PrayerIshaAdjustPlus->setVisible(PrayerTimeVisible);
    PrayerIshaAdjustMinus->setVisible(PrayerTimeVisible);
    FajerEditLabel->setVisible(PrayerTimeVisible);
    ShrouqEditLabel->setVisible(PrayerTimeVisible);
    DhuhrEditLabel->setVisible(PrayerTimeVisible);
    AsrEditLabel->setVisible(PrayerTimeVisible);
    MagribEditLabel->setVisible(PrayerTimeVisible);
    IshaEditLabel->setVisible(PrayerTimeVisible);
    FajerEditLabel->setText(QVariant(*addedTimeFajer).toString());
    ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
    DhuhrEditLabel->setText(QVariant(*addedTimeDhuhr).toString());
    AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
    MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
    IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());




}
void MainWindow::ActivePrayerMenu(){
    PrayerEditVisible=!PrayerEditVisible;

  //  PrayerEditButton->setVisible(PrayerEditVisible);
   // iqamahEditButton->setVisible(PrayerEditVisible);

}
void MainWindow::PrayerEdit(QSize size, int PositionX, int PositionY){

    // QString Fajer = QString::number(addedTimeFajer,'f',0);
      // QString Shrouq = QString::number(addedTimeShrouq,'f',0);
      // QString Dhuhr = QString::number(addedTimeDhuhr,'f',0);
      // QString Asr = QString::number(addedTimeAsr,'f',0);
      // QString Magrib = QString::number(addedTimeMagrib,'f',0);
      // QString Isha = QString::number(addedTimeIsha,'f',0);
      // qDebug()<<Fajer<<Shrouq<<Dhuhr<<Asr<<Magrib<<Isha;

    if(*ArabicLang){
       FajerEditLabel->setGeometry(QRect(FajerLabel->geometry().x()-FajerLabel->geometry().width()-size.width()-10,FajerTimeLabel->geometry().y(),size.width(),size.height()));
    }else{
      FajerEditLabel->setGeometry(QRect(FajerTimeLabel->geometry().width()+size.width(),FajerTimeLabel->geometry().y(),size.width(),size.height()));

    }
       FajerEditLabel->setProperty("Type",1);
       FajerEditLabel->style()->polish(this);
       FajerEditLabel->style()->unpolish(this);
       FajerEditLabel->setStyleSheet(CssFile);
       if(PrayerTimeVisible==true){
       FajerEditLabel->setText(QString::number(*addedTimeFajer));
       }if(iqamahActive==true){
           FajerEditLabel->setText(QString::number(*iqamahTimeFajer));
       }
       FajerEditLabel->show();

       PrayerFajerAdjustPlus->setGeometry(QRect(FajerEditLabel->pos().x()+FajerEditLabel->geometry().width()-50,FajerEditLabel->pos().y(),50,50));
       PrayerFajerAdjustPlus->setText("+");
       PrayerFajerAdjustPlus->setProperty("Type",16);
       PrayerFajerAdjustPlus->style()->polish(this);
       PrayerFajerAdjustPlus->style()->unpolish(this);
       PrayerFajerAdjustPlus->raise();
       PrayerFajerAdjustPlus->setStyleSheet(CssFile);
       PrayerFajerAdjustPlus->show();

       PrayerFajerAdjustMinus->setGeometry(QRect(FajerEditLabel->pos().x(),FajerEditLabel->pos().y(),50,50));
       PrayerFajerAdjustMinus->setText("-");
       PrayerFajerAdjustMinus->setProperty("Type",16);
       PrayerFajerAdjustMinus->style()->polish(this);
       PrayerFajerAdjustMinus->style()->unpolish(this);
       PrayerFajerAdjustMinus->raise();
       PrayerFajerAdjustMinus->setStyleSheet(CssFile);
       PrayerFajerAdjustMinus->show();

       //--------->> Sharouq

        if(*ArabicLang){
       ShrouqEditLabel->setGeometry(QRect(SharouqLabel->geometry().x()-SharouqLabel->geometry().width()-size.width()-10,SharouqTimeLabel->geometry().y(),size.width(),size.height()));
        }else{

            ShrouqEditLabel->setGeometry(QRect(SharouqTimeLabel->geometry().x()+size.width()-10,SharouqTimeLabel->geometry().y(),size.width(),size.height()));

        }
       ShrouqEditLabel->setProperty("Type",1);
       ShrouqEditLabel->style()->polish(this);
       ShrouqEditLabel->style()->unpolish(this);
       ShrouqEditLabel->setStyleSheet(CssFile);
       if(PrayerTimeVisible==true){
       ShrouqEditLabel->setText(QString::number(*addedTimeShrouq));
       }
       if(iqamahActive==true){
       ShrouqEditLabel->setText(QString::number(*iqamahTimeShrouq));
       }
       ShrouqEditLabel->show();

       PrayerSharouqAdjustPlus->setGeometry(QRect(ShrouqEditLabel->pos().x()+ShrouqEditLabel->geometry().width()-50,ShrouqEditLabel->pos().y(),50,50));
       PrayerSharouqAdjustPlus->setText("+");
       PrayerSharouqAdjustPlus->setProperty("Type",16);
       PrayerSharouqAdjustPlus->style()->polish(this);
       PrayerSharouqAdjustPlus->style()->unpolish(this);
       PrayerSharouqAdjustPlus->raise();
       PrayerSharouqAdjustPlus->setStyleSheet(CssFile);
       PrayerSharouqAdjustPlus->show();

       PrayerSharouqAdjustMinus->setGeometry(QRect(ShrouqEditLabel->pos().x(),ShrouqEditLabel->pos().y(),50,50));
       PrayerSharouqAdjustMinus->setText("-");
       PrayerSharouqAdjustMinus->setProperty("Type",16);
       PrayerSharouqAdjustMinus->style()->polish(this);
       PrayerSharouqAdjustMinus->style()->unpolish(this);
       PrayerSharouqAdjustMinus->raise();
       PrayerSharouqAdjustMinus->setStyleSheet(CssFile);
       PrayerSharouqAdjustMinus->show();

       //--------->>Dhuhr
       if(*ArabicLang){
       DhuhrEditLabel->setGeometry(QRect(DhuhrLabel->geometry().x()-DhuhrLabel->geometry().width()-size.width()-10,DhuhrTimeLabel->geometry().y(),size.width(),size.height()));
       }else {
       DhuhrEditLabel->setGeometry(QRect(DhuhrTimeLabel->geometry().x()+size.width()-10,DhuhrTimeLabel->geometry().y(),size.width(),size.height()));


       }

       DhuhrEditLabel->setProperty("Type",1);
       DhuhrEditLabel->style()->polish(this);
       DhuhrEditLabel->style()->unpolish(this);
       DhuhrEditLabel->setStyleSheet(CssFile);
       if(PrayerTimeVisible==true){
       DhuhrEditLabel->setText(QString::number(*addedTimeDhuhr));
       }
       if(iqamahActive==true){
       DhuhrEditLabel->setText(QString::number(*iqamahTimeDhuhr));
       }
       DhuhrEditLabel->show();

       PrayerDhuhrAdjustPlus->setGeometry(QRect(DhuhrEditLabel->pos().x()+DhuhrEditLabel->geometry().width()-50,DhuhrEditLabel->pos().y(),50,50));
       PrayerDhuhrAdjustPlus->setText("+");
       PrayerDhuhrAdjustPlus->setProperty("Type",16);
       PrayerDhuhrAdjustPlus->style()->polish(this);
       PrayerDhuhrAdjustPlus->style()->unpolish(this);
       PrayerDhuhrAdjustPlus->raise();
       PrayerDhuhrAdjustPlus->setStyleSheet(CssFile);
       PrayerDhuhrAdjustPlus->show();

       PrayerDhuhrAdjustMinus->setGeometry(QRect(DhuhrEditLabel->pos().x(),DhuhrEditLabel->pos().y(),50,50));
       PrayerDhuhrAdjustMinus->setText("-");
       PrayerDhuhrAdjustMinus->setProperty("Type",16);
       PrayerDhuhrAdjustMinus->style()->polish(this);
       PrayerDhuhrAdjustMinus->style()->unpolish(this);
       PrayerDhuhrAdjustMinus->raise();
       PrayerDhuhrAdjustMinus->setStyleSheet(CssFile);
       PrayerDhuhrAdjustMinus->show();


    //------->> Asr
       if(*ArabicLang){
       AsrEditLabel->setGeometry(QRect(AsrLabel->geometry().x()-AsrLabel->geometry().width()-size.width()-10,AsrTimeLabel->geometry().y(),size.width(),size.height()));
       }else{
        AsrEditLabel->setGeometry(QRect(AsrTimeLabel->geometry().x()+size.width()-10,AsrTimeLabel->geometry().y(),size.width(),size.height()));

       }
       AsrEditLabel->setProperty("Type",1);
       AsrEditLabel->style()->polish(this);
       AsrEditLabel->style()->unpolish(this);
       AsrEditLabel->setStyleSheet(CssFile);
       if(PrayerTimeVisible==true){
       AsrEditLabel->setText(QString::number(*addedTimeAsr));
       }
       if(iqamahActive==true){
       AsrEditLabel->setText(QString::number(*iqamahTimeAsr));
       }
       AsrEditLabel->show();

       PrayerAsrAdjustPlus->setGeometry(QRect(AsrEditLabel->pos().x()+AsrEditLabel->geometry().width()-50,AsrEditLabel->pos().y(),50,50));
       PrayerAsrAdjustPlus->setText("+");
       PrayerAsrAdjustPlus->setProperty("Type",16);
       PrayerAsrAdjustPlus->style()->polish(this);
       PrayerAsrAdjustPlus->style()->unpolish(this);
       PrayerAsrAdjustPlus->raise();
       PrayerAsrAdjustPlus->setStyleSheet(CssFile);
       PrayerAsrAdjustPlus->show();

       PrayerAsrAdjustMinus->setGeometry(QRect(AsrEditLabel->pos().x(),AsrEditLabel->pos().y(),50,50));
       PrayerAsrAdjustMinus->setText("-");
       PrayerAsrAdjustMinus->setProperty("Type",16);
       PrayerAsrAdjustMinus->style()->polish(this);
       PrayerAsrAdjustMinus->style()->unpolish(this);
       PrayerAsrAdjustMinus->raise();
       PrayerAsrAdjustMinus->setStyleSheet(CssFile);
       PrayerAsrAdjustMinus->show();


       //--------->>> Magrib
       if(*ArabicLang){
       MagribEditLabel->setGeometry(QRect(MagribLabel->geometry().x()-MagribLabel->geometry().width()-size.width()-10,MagribTimeLabel->geometry().y(),size.width(),size.height()));
       }else{
       MagribEditLabel->setGeometry(QRect(MagribTimeLabel->geometry().x()+size.width()-10,MagribTimeLabel->geometry().y(),size.width(),size.height()));
       }
       MagribEditLabel->setProperty("Type",1);
       MagribEditLabel->style()->polish(this);
       MagribEditLabel->style()->unpolish(this);
       MagribEditLabel->setStyleSheet(CssFile);
       if(PrayerTimeVisible==true){
       MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
       }
       if(iqamahActive==true){
       MagribEditLabel->setText(QVariant(*iqamahTimeMagrib).toString());
       }
       MagribEditLabel->show();

       PrayerMagribAdjustPlus->setGeometry(QRect(MagribEditLabel->pos().x()+MagribEditLabel->geometry().width()-50,MagribEditLabel->pos().y(),50,50));
       PrayerMagribAdjustPlus->setText("+");
       PrayerMagribAdjustPlus->setProperty("Type",16);
       PrayerMagribAdjustPlus->style()->polish(this);
       PrayerMagribAdjustPlus->style()->unpolish(this);
       PrayerMagribAdjustPlus->raise();
       PrayerMagribAdjustPlus->setStyleSheet(CssFile);
       PrayerMagribAdjustPlus->show();

       PrayerMagribAdjustMinus->setGeometry(QRect(MagribEditLabel->pos().x(),MagribEditLabel->pos().y(),50,50));
       PrayerMagribAdjustMinus->setText("-");
       PrayerMagribAdjustMinus->setProperty("Type",16);
       PrayerMagribAdjustMinus->style()->polish(this);
       PrayerMagribAdjustMinus->style()->unpolish(this);
       PrayerMagribAdjustMinus->raise();
       PrayerMagribAdjustMinus->setStyleSheet(CssFile);
       PrayerMagribAdjustMinus->show();

       //----->> Isha

       if(*ArabicLang){
       IshaEditLabel->setGeometry(QRect(IshaLabel->geometry().x()-IshaLabel->geometry().width()-size.width()-10,IshaTimeLabel->geometry().y(),size.width(),size.height()));
       }else{
       IshaEditLabel->setGeometry(QRect(IshaTimeLabel->geometry().x()+size.width()-10,IshaTimeLabel->geometry().y(),size.width(),size.height()));
       }
       IshaEditLabel->setProperty("Type",1);
       IshaEditLabel->style()->polish(this);
       IshaEditLabel->style()->unpolish(this);
       IshaEditLabel->setStyleSheet(CssFile);
       if(PrayerTimeVisible==true){
       IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());
       }
       if(iqamahActive==true){
       IshaEditLabel->setText(QVariant(*iqamahTimeIsha).toString());
       }
       IshaEditLabel->show();

       PrayerIshaAdjustPlus->setGeometry(QRect(IshaEditLabel->pos().x()+IshaEditLabel->geometry().width()-50,IshaEditLabel->pos().y(),50,50));
       PrayerIshaAdjustPlus->setText("+");
       PrayerIshaAdjustPlus->setProperty("Type",16);
       PrayerIshaAdjustPlus->style()->polish(this);
       PrayerIshaAdjustPlus->style()->unpolish(this);
       PrayerIshaAdjustPlus->raise();
       PrayerIshaAdjustPlus->setStyleSheet(CssFile);
       PrayerIshaAdjustPlus->show();

       PrayerIshaAdjustMinus->setGeometry(QRect(IshaEditLabel->pos().x(),IshaEditLabel->pos().y(),50,50));
       PrayerIshaAdjustMinus->setText("-");
       PrayerIshaAdjustMinus->setProperty("Type",16);
       PrayerIshaAdjustMinus->style()->polish(this);
       PrayerIshaAdjustMinus->style()->unpolish(this);
       PrayerIshaAdjustMinus->raise();
       PrayerIshaAdjustMinus->setStyleSheet(CssFile);
       PrayerIshaAdjustMinus->show();
}
void MainWindow::showTime(){
    // displaying ":" after every second on the clock
        QTime time =  QTime::currentTime();// current time
        QString text = time.toString("hh:mm");
       if ((time.second() % 2) == 0)
           text[2] = ' ';
    ClockLabel->setText(text);


    if(sleep_no){

        system("vcgencmd display_power 1");
    }

    if(ClockLabel->text()==FajerTimeLabel->text())    {
        timer1->start(10);
        iqamahTimer->start(60000);
        currentPrayer="Fajer";
        iqamahMessageLabel->setText("حان موعد اذان صلاة الفجر \n Time now for Fajer Adan");
        iqamahFajerCounter=*iqamahTimeFajer;
        if(sleep_def){

            system("vcgencmd display_power 1");
        }
        if(a_fajer & time.second()<2){

            // ...
            player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/azan/Fajer.mp3"));
            player->setVolume(volume);
            player->play();
        }

    }
    if(ClockLabel->text()==DhuhrTimeLabel->text()){
        timer1->start(10);
        iqamahTimer->start(60000);
        currentPrayer="Dhuhr";
        iqamahMessageLabel->setText("حان موعد اذان صلاة الظهر \n Time now for Dhuhr Adan");
        iqamahDhuhrCounter=*iqamahTimeDhuhr;
        if(sleep_def){

            system("vcgencmd display_power 1");
        }
         if(a_dhuhr & time.second()<2){
        player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/azan/Dhuhr.mp3"));
        player->setVolume(volume);
        player->play();
         }

    }
    if(ClockLabel->text()==AsrTimeLabel->text())    {
        timer1->start(10);
        iqamahTimer->start(60000);
        currentPrayer="Asr";
        iqamahMessageLabel->setText("حان موعد اذان صلاة العصر \n Time now for Asr Adan");
        iqamahAsrCounter=*iqamahTimeAsr;
        if(sleep_def){

            system("vcgencmd display_power 1");
        }
        if(a_asr & time.second()<2){
            player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/azan/Asr.mp3"));
            player->setVolume(volume);
            player->play();

        }

      }

    if(ClockLabel->text()==MagribTimeLabel->text())    {
        timer1->start(10);
        iqamahTimer->start(60000);
        currentPrayer="Magrib";
        iqamahMessageLabel->setText("حان موعد اذان صلاة المغرب \n Time now for Magrib Adan");
        iqamahMagribCounter=*iqamahTimeMagrib;
        if(sleep_def){

            system("vcgencmd display_power 1");
        }
        if(a_mgrib & time.second()<2){
            player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/azan/Magrib.mp3"));
            player->setVolume(volume);
            player->play();

        }
    }

    if(ClockLabel->text()==IshaTimeLabel->text())    {
         iqamahIshaCounter=*iqamahTimeIsha;
        timer1->start(10);
        iqamahTimer->start(60000);
        currentPrayer="Isha";
        iqamahMessageLabel->setText("حان موعد اذان صلاة العشاء \n Time now for Isha Adan");
        if(sleep_def){

            system("vcgencmd display_power 1");
        }
        if(a_isha & time.second()<2){
            player->setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/azan/Isha.mp3"));
            player->setVolume(volume);
            player->play();
            qDebug()<<"Azan ish is working "<<endl;

        }

    }

    if(time.toString("hh:mm:ss")=="00:01:00"){
        UpdateHadithQuranInterface();
        RefreshTimes(UPDATE::ALL);
        this->setStyleSheet(StyleSheetFile.BackgroundChanging(ApplicationPath));
    }

}
void MainWindow::IncreaseTime(QString whichButton){
if(whichButton=="InFajer"){
    if(PrayerTimeVisible==true){
    addedTimeFajer_v++;
    FajerEditLabel->setText(QVariant(*addedTimeFajer).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeFajer",*addedTimeFajer);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }

    if(iqamahActive==true){
    iqamahTimeFajer_v++;
    //FajerEditLabel->setText(QVariant(*iqamahTimeFajer).toString());
    Settings.StoreSettings("iqamahAdjustment","iqamahTimeFajer",*iqamahTimeFajer);
    RefreshTimes(UPDATE::IQAMAH);

    }


}


if(whichButton=="DecFajer"){

    if(PrayerTimeVisible==true){
    addedTimeFajer_v--;
    FajerEditLabel->setText(QVariant(*addedTimeFajer).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeFajer",*addedTimeFajer);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }

    if(iqamahActive==true){

     iqamahTimeFajer_v--;
    //FajerEditLabel->setText(QVariant(*iqamahTimeFajer).toString());
    Settings.StoreSettings("iqamahAdjustment","iqamahTimeFajer",*iqamahTimeFajer);
    RefreshTimes(UPDATE::IQAMAH);

    }


}
if(whichButton=="InShrouq"){
    if(PrayerTimeVisible==true){
    addedTimeShrouq_v++;
    ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeShrouq",*addedTimeShrouq);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){
        iqamahTimeShrouq_v++;
        //ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeShrouq",*iqamahTimeShrouq);
        RefreshTimes(UPDATE::IQAMAH);


    }

}
if(whichButton=="DecShrouq"){

    if(PrayerTimeVisible==true){
    addedTimeShrouq_v--;
    ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeShrouq",*addedTimeShrouq);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){

        iqamahTimeShrouq_v--;
        //ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeShrouq",*iqamahTimeShrouq);
        RefreshTimes(UPDATE::IQAMAH);

    }

}
if(whichButton=="InDhuhr"){
    if(PrayerTimeVisible==true){
    addedTimeDhuhr_v++;
    DhuhrEditLabel->setText(QVariant(*addedTimeDhuhr).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeDhuhr",*addedTimeDhuhr);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){

        iqamahTimeDhuhr_v++;
       // DhuhrEditLabel->setText(QVariant(*iqamahTimeDhuhr).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeDhuhr",*iqamahTimeDhuhr);
        RefreshTimes(UPDATE::IQAMAH);


    }

}
if(whichButton=="DecDhuhr"){
    if(PrayerTimeVisible==true){
    addedTimeDhuhr_v--;
    DhuhrEditLabel->setText(QVariant(*addedTimeDhuhr).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeDhuhr",*addedTimeDhuhr);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){

        iqamahTimeDhuhr_v--;
       // DhuhrEditLabel->setText(QVariant(*iqamahTimeDhuhr).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeDhuhr",*iqamahTimeDhuhr);
        RefreshTimes(UPDATE::IQAMAH);


    }

}
if(whichButton=="InAsr"){
    if(PrayerTimeVisible==true){
    addedTimeAsr_v++;
    AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeAsr",*addedTimeAsr);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){
        iqamahTimeAsr_v++;
        //AsrEditLabel->setText(QVariant(*iqamahTimeAsr).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeAsr",*iqamahTimeAsr);
        RefreshTimes(UPDATE::IQAMAH);

    }

}
if(whichButton=="DecAsr"){
    if(PrayerTimeVisible==true){
    addedTimeAsr_v--;
    AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeAsr",*addedTimeAsr);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){

        iqamahTimeAsr_v--;
        //AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeAsr",*iqamahTimeAsr);
        RefreshTimes(UPDATE::IQAMAH);

    }

}
if(whichButton=="InMagrib"){
    if(PrayerTimeVisible==true)
    {
    addedTimeMagrib_v++;
    MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeMagrib",*addedTimeMagrib);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){
        iqamahTimeMagrib_v++;
        //MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeMagrib",*iqamahTimeMagrib);
        RefreshTimes(UPDATE::IQAMAH);

    }

}
if(whichButton=="DecMagrib"){

    if(PrayerTimeVisible==true){
    addedTimeMagrib_v--;
    MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeMagrib",*addedTimeMagrib);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){
        iqamahTimeMagrib_v--;
        //MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeMagrib",*iqamahTimeMagrib);
        RefreshTimes(UPDATE::IQAMAH);

    }

}
if(whichButton=="InIsha"){
    if(PrayerTimeVisible==true){
    addedTimeIsha_v++;
    IshaEditLabel->setText(QVariant(*addedTimeIsha).toString()); //QVariant(*addedTimeIsha).toString()
    Settings.StoreSettings("PrayerAdjustment","AddedTimeIsha",*addedTimeIsha);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){

        iqamahTimeIsha_v++;
        //IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeIsha",*iqamahTimeIsha);
        RefreshTimes(UPDATE::IQAMAH);

    }

}
if(whichButton=="DecIsha"){
    if(PrayerTimeVisible==true){

    addedTimeIsha_v--;
    IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());
    Settings.StoreSettings("PrayerAdjustment","AddedTimeIsha",*addedTimeIsha);
    RefreshTimes(UPDATE::PRAYER_ADD);

    }
    if(iqamahActive==true){
        iqamahTimeIsha_v--;
        //IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());
        Settings.StoreSettings("iqamahAdjustment","iqamahTimeIsha",*iqamahTimeIsha);
        RefreshTimes(UPDATE::IQAMAH);

    }


}
}
void MainWindow::AnimationUp(){
    if(*index>=ScreenSize1.height()-300){
    height--;
    iqamahMessageLabel->setGeometry(QRect(0,*index,ScreenSize1.width(),400));

    }else{

        timer1->stop();

    }
}
void MainWindow::AnimationDown(){

    if(*index!=ScreenSize1.height()){
    height++;
    iqamahMessageLabel->setGeometry(QRect(0,*index,ScreenSize1.width(),400));

    }else{

        timer2->stop();
    }


        }
void MainWindow::HadithQuran(int &XPosition, int &YPosition){

      if(*ArabicLang==true){
    HadithQuranTabLabel->setGeometry(QRect(XPosition+ScreenSize1.width()-400,YPosition-405,400,100));
    HadithQuranTabLabel->setProperty("Type",14);
    HadithQuranTabLabel->style()->polish(this);
    HadithQuranTabLabel->style()->unpolish(this);
    HadithQuranTabLabel->setWordWrap(true);
    //HadithQuranTabLabel->setText("حديث اليوم : قال رسول الله");
    //HadithQuranTabLabel->setAlignment(Qt::AlignTop);
    HadithQuranTabLabel->setAlignment(Qt::AlignCenter);
    HadithQuranTabLabel->setStyleSheet(CssFile);
    HadithQuranTabLabel->show();
} else {

          HadithQuranTabLabel->setGeometry(QRect(XPosition,YPosition-405,400,100));
          HadithQuranTabLabel->setProperty("Type",14);
          HadithQuranTabLabel->style()->polish(this);
          HadithQuranTabLabel->style()->unpolish(this);
          HadithQuranTabLabel->setWordWrap(true);
          //HadithQuranTabLabel->setText("حديث اليوم : قال رسول الله");
          //HadithQuranTabLabel->setAlignment(Qt::AlignTop);
          HadithQuranTabLabel->setAlignment(Qt::AlignCenter);
          HadithQuranTabLabel->setStyleSheet(CssFile);
          HadithQuranTabLabel->show();

      }

    HadithQuranLabel->setGeometry(QRect(XPosition,YPosition-300,ScreenSize1.width(),300));
    HadithQuranLabel->setProperty("Type",13);
    HadithQuranLabel->style()->polish(this);
    HadithQuranLabel->style()->unpolish(this);
 //   HadithQuranLabel->setAlignment(Qt::AlignTop);
    HadithQuranLabel->setAlignment(Qt::AlignCenter);
    HadithQuranLabel->setWordWrap(true);

    HadithQuranLabel->setStyleSheet(CssFile);
    HadithQuranLabel->show();

}
void MainWindow::RefreshTimes(int UPDATE){
 // prayer update
if(UPDATE==UPDATE::PRAYER_METHOD | UPDATE==UPDATE::ALL){
    double times[PrayerTimes::TimesCount];

    double latitude = Settings.ReadSettings("GPS_Information","Latitude").toDouble();//50.8357;		// 35.7061
    double longitude = Settings.ReadSettings("GPS_Information","Langitud").toDouble();	// 51.4358
    double timezone =Settings.ReadSettings("LocalSettings","TimeZone").toDouble();
    time_t date = time(NULL);
    prayer_times.get_prayer_times(date, latitude, longitude, timezone, times);
    QString FajerTime= QVariant(PrayerTimes::float_time_to_time24(times[0]).c_str()).toString();
    QString ShrouqTime= QVariant(PrayerTimes::float_time_to_time24(times[1]).c_str()).toString();
    QString DhuhrTime= QVariant(PrayerTimes::float_time_to_time24(times[2]).c_str()).toString();
    QString AsrTime= QVariant(PrayerTimes::float_time_to_time24(times[3]).c_str()).toString();
    QString MagribTime= QVariant(PrayerTimes::float_time_to_time24(times[5]).c_str()).toString();
    QString IshaTime= QVariant(PrayerTimes::float_time_to_time24(times[6]).c_str()).toString();
    if(Settings.ReadSettings("PrayerSettings","Method").toString()=="Diyanet"){
         QSqlQuery Diyanet;
        if(QDate::currentDate().month()>8){

        QString Date1="2018-"+ QDate::currentDate().toString("MM-dd");
        Diyanet= Database.DiyanetData(Date1);
        Diyanet.first();
        }else{

            QString Date1="2019-"+ QDate::currentDate().toString("MM-dd");

         Diyanet= Database.DiyanetData(Date1);
        Diyanet.first();
        qDebug()<<"Diyanet "<<"Fajer"<<Date1<<"Sharouq"<<Diyanet.value(1).toString();
        qDebug()<<"It works Diyanet";

        }
        Fajer=QVariant(Diyanet.value(0)).toTime();
        Shrouq=QVariant(Diyanet.value(1)).toTime();
        Dhuhr=QVariant(Diyanet.value(2)).toTime();
        Asr=QVariant(Diyanet.value(3)).toTime();
        Magrib=QVariant(Diyanet.value(4)).toTime();
        Isha=QVariant(Diyanet.value(5)).toTime();


    }else if(Settings.ReadSettings("PrayerSettings","Method").toString()=="Database"){
        QSqlQuery database;
        QString Date2=QDate::currentDate().toString("yyyy-MM-dd");
        database=Database.database_method(Date2);
        database.first();
        qDebug()<<"Diyanet "<<"Fajer"<<database.value(1)<<"Sharouq"<<database.value(0);

        Fajer=QVariant(database.value(0)).toTime();
        Shrouq=QVariant(database.value(1)).toTime();
        Dhuhr=QVariant(database.value(2)).toTime();
        Asr=QVariant(database.value(3)).toTime();
        Magrib=QVariant(database.value(4)).toTime();
        Isha=QVariant(database.value(5)).toTime();



    }else{

        double times[PrayerTimes::TimesCount];

        double latitude = Settings.ReadSettings("GPS_Information","Latitude").toDouble();//50.8357;		// 35.7061
        double longitude = Settings.ReadSettings("GPS_Information","Langitud").toDouble();	// 51.4358
        double timezone =Settings.ReadSettings("LocalSettings","TimeZone").toDouble();
        time_t date = time(NULL);
        prayer_times.get_prayer_times(date, latitude, longitude, timezone, times);
        QString FajerTime= QVariant(PrayerTimes::float_time_to_time24(times[0]).c_str()).toString();
        QString ShrouqTime= QVariant(PrayerTimes::float_time_to_time24(times[1]).c_str()).toString();
        QString DhuhrTime= QVariant(PrayerTimes::float_time_to_time24(times[2]).c_str()).toString();
        QString AsrTime= QVariant(PrayerTimes::float_time_to_time24(times[3]).c_str()).toString();
        QString MagribTime= QVariant(PrayerTimes::float_time_to_time24(times[5]).c_str()).toString();
        QString IshaTime= QVariant(PrayerTimes::float_time_to_time24(times[6]).c_str()).toString();
    Isha= QVariant(IshaTime).toTime();
    Magrib= QVariant(MagribTime).toTime();
    Asr= QVariant(AsrTime).toTime();
    Dhuhr= QVariant(DhuhrTime).toTime();
    Shrouq= QVariant(ShrouqTime).toTime();
    Fajer= QVariant(FajerTime).toTime();
    }
    }
 //update the times of prayers
if(UPDATE==UPDATE::PRAYER_ADD | UPDATE==UPDATE::ALL){
    FajerTimeLabel->setText(Fajer.addSecs((*addedTimeFajer)*60).toString("hh:mm"));
    SharouqTimeLabel->setText(Shrouq.addSecs((*addedTimeShrouq)*60).toString("hh:mm"));
    DhuhrTimeLabel->setText(Dhuhr.addSecs((*addedTimeDhuhr)*60).toString("hh:mm"));
    AsrTimeLabel->setText(Asr.addSecs((*addedTimeAsr)*60).toString("hh:mm"));
    MagribTimeLabel->setText(Magrib.addSecs((*addedTimeMagrib)*60).toString("hh:mm"));
    IshaTimeLabel->setText(Isha.addSecs((*addedTimeIsha)*60).toString("hh:mm"));

    if(PrayerEditVisible){
    FajerEditLabel->setText(QVariant(*addedTimeFajer).toString());
    ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
    DhuhrEditLabel->setText(QVariant(*addedTimeDhuhr).toString());
    AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
    MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
    IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());
}
    }
 // update the iqaham prayers
if(UPDATE==UPDATE::IQAMAH | UPDATE==UPDATE::ALL){
    if(iqamahActive){
    FajerEditLabel->setText(QVariant(*iqamahTimeFajer).toString());
    ShrouqEditLabel->setText(QVariant(*iqamahTimeShrouq).toString());
    DhuhrEditLabel->setText(QVariant(*iqamahTimeDhuhr).toString());
    AsrEditLabel->setText(QVariant(*iqamahTimeAsr).toString());
    MagribEditLabel->setText(QVariant(*iqamahTimeMagrib).toString());
    IshaEditLabel->setText(QVariant(*iqamahTimeIsha).toString());

}
}
 // thema change
if(UPDATE==UPDATE::THEME | UPDATE==UPDATE::ALL){
 if(ThemaChange){
  //  PrayerTimeEditButton->setVisible(false);

     QSize  ScreenSize=Screen.ScreenSize();
     QSize sizeofclock(300,400);
     QSize sizeofPrayer(300,100);
     QSize sizeofPrayerEdit(250,50);
     QSize sizeofIslamicEvent(40,400);//40
     //--->> Widegts

     int PrayerWidgetPositionSpace=40;
     PrayerWidget(sizeofPrayer,ScreenSize.width()-sizeofPrayer.width()-20,10,PrayerWidgetPositionSpace, *ArabicLang);
     ClockWidget(sizeofclock,ClockPosition[0],ClockPosition[1]);

     PrayerEdit(sizeofPrayerEdit,0,0);
     TodayIslamicEvent(sizeofIslamicEvent,ClockPosition[0],sizeofIslamicEvent.height()-75);
     QSize ButtonSize(35,75);

     SettingPushButtonWidget(ButtonSize,ScreenSize.width(),ScreenSize.height());
     PrayerEditPushButtonWidget(ButtonSize,ScreenSize.width(),ScreenSize.height());

     int x=0;
     int y=ScreenSize1.height();
     HadithQuran(x,y);


     TimeEditButton->setVisible(false);
    ClockAdjustmentminus->setVisible(false);
    ClockAdjustmentplus->setVisible(false);
    ClockAdjustmentLabel->setVisible(false);
    PrayerFajerAdjustPlus->setVisible(false);
    PrayerFajerAdjustMinus->setVisible(false);
    PrayerSharouqAdjustPlus->setVisible(false);
    PrayerSharouqAdjustMinus->setVisible(false);
    PrayerDhuhrAdjustPlus->setVisible(false);
    PrayerDhuhrAdjustMinus->setVisible(false);
    PrayerAsrAdjustPlus->setVisible(false);
    PrayerAsrAdjustMinus->setVisible(false);
    PrayerMagribAdjustPlus->setVisible(false);
    PrayerMagribAdjustMinus->setVisible(false);
    PrayerIshaAdjustPlus->setVisible(false);
    PrayerIshaAdjustMinus->setVisible(false);
    FajerEditLabel->setVisible(false);
    ShrouqEditLabel->setVisible(false);
    DhuhrEditLabel->setVisible(false);
    AsrEditLabel->setVisible(false);
    MagribEditLabel->setVisible(false);
    IshaEditLabel->setVisible(false);
    HijriEditLabel->setVisible(false);
    HijriMinus->setVisible(false);
    HijriPlus->setVisible(false);
    HijriMinus->raise();
    HijriPlus->raise();
    if(IslamicEventContent->text()=="")
        IslamicEventContent->setVisible(false);
    if(IslamicEventTitle->text()=="")
        IslamicEventTitle->setVisible(false);

    //this->setStyleSheet(StyleSheetFile.BackgroundChanging(ApplicationPath));
        RefreshTimes(UPDATE::LANG);

    ThemaChange=false;
}
}
 //dates change
if(UPDATE==UPDATE::DATE | UPDATE==UPDATE::ALL){
 int day = QDate::currentDate().day();
 int month = QDate::currentDate().month();
 int year = QDate::currentDate().year();
 QString date1 = HijriDate.PrintCalender(day+HijriAddedDays_v,month,year,0);
 HijriLabel->setText(date1);
 GregorianLabel->setText(QDate::currentDate().toString("yyyy-MMMM-dd"));

}
 //language change
if(UPDATE== UPDATE::LANG | UPDATE==UPDATE::ALL){
    int PrayerWidgetPositionSpace=10;
    QSize  ScreenSize=Screen.ScreenSize();
    QSize sizeofPrayer(300,100);

         if(*ArabicLang==true){
             QSize sizeofclock(300,400);
             QSize sizeofPrayer(300,100);
             QSize sizeofPrayerEdit(250,50);
             QSize sizeofIslamicEvent(40,400);//40
             //--->> Widegts


             PrayerWidget(sizeofPrayer,ScreenSize.width()-sizeofPrayer.width()-20,10,PrayerWidgetPositionSpace, *ArabicLang);
             ClockWidget(sizeofclock,ClockPosition[0],ClockPosition[1]);

             PrayerEdit(sizeofPrayerEdit,0,0);
             TodayIslamicEvent(sizeofIslamicEvent,ClockPosition[0],sizeofIslamicEvent.height()-75);
             QSize ButtonSize(35,75);

             SettingPushButtonWidget(ButtonSize,ScreenSize.width(),ScreenSize.height());
             PrayerEditPushButtonWidget(ButtonSize,ScreenSize.width(),ScreenSize.height());

             int x=0;
             int y=ScreenSize1.height();
             HadithQuran(x,y);
             PrayerFajerAdjustPlus->setVisible(false);
             PrayerFajerAdjustMinus->setVisible(false);
             PrayerSharouqAdjustPlus->setVisible(false);
             PrayerSharouqAdjustMinus->setVisible(false);
             PrayerDhuhrAdjustPlus->setVisible(false);
             PrayerDhuhrAdjustMinus->setVisible(false);
             PrayerAsrAdjustPlus->setVisible(false);
             PrayerAsrAdjustMinus->setVisible(false);
             PrayerMagribAdjustPlus->setVisible(false);
             PrayerMagribAdjustMinus->setVisible(false);
             PrayerIshaAdjustPlus->setVisible(false);
             PrayerIshaAdjustMinus->setVisible(false);
             FajerEditLabel->setVisible(false);
             ShrouqEditLabel->setVisible(false);
             DhuhrEditLabel->setVisible(false);
             AsrEditLabel->setVisible(false);
             MagribEditLabel->setVisible(false);
             IshaEditLabel->setVisible(false);
             HijriPlus->setVisible(false);
             HijriMinus->setVisible(false);
             HijriEditLabel->setVisible(false);
           //  HijriLabel->setVisible(false);

         Time->setText("التاريخ الهجري");
         EditTimePrayers->setText("تعديل اوقات الصلاة");
         EditTimeIqamah->setText("تعديل اوقات الاقامة");
         English->setText("انكليزي");
         Arabic->setText("عربي");
         AddingMessageMenu->setTitle("اضافة رسالة");
         PrayersMenu->setTitle("اوقات الصلاة");
         TimeMenu->setTitle("تعديل التاريخ الهجري");
         Language->setTitle("اللغة");
         InterfaceThema->setTitle("المظهر");
         SettingButton->setText("الاعدادات");
         SettingMenu->setTitle("الاعدادات");
         FactoryResetMenu->setTitle("استعادة الاعدادات الافتراضية");
         BlackThema->setText("مظهر الاسود");
         WhiteThema->setText("مظهر الابيض");
         AddMessage->setText("اضافة رسالة");
         FactoryReset->setText("اعادة ضبط المصنع");
         DefaultConfig->setText("الاعدادات الافتراضية");
         AzanSettings->setTitle("اعدادت الاذان");
         AzanSettings_azan->setTitle("تفعيل الاذان");
         AzanSettings_Mothen->setTitle("المؤذن");
         Fajer_azan->setText("الفجر");
         Dhuhr_azan->setText("الظهر");
         Asr_azan->setText("العصر");
         Magrib_azan->setText("المغرب");
         Isha_azan->setText("عشاء");
         Sleep_None->setText("دائما");
         Sleep_Default->setText("عند الاذان");
         Sleeping_Mode->setTitle("تفعيل الشاشة");
         wireless->setText("الاتصال بشبكة لاسلكية");
         database->setText("مزامنة قاعدة البيانات");
         reboot->setText("اعادة التشغيل");
         shutdown->setText("أوقف التشغيل");


         }else
         {
             QSize sizeofIslamicEvent(40,400);//40

            int posx=ScreenSize1.width()-sizeofclock.height()-10;
             ClockWidget(sizeofclock,posx,ClockPosition[1]);
             PrayerWidget(sizeofPrayer,10,10,PrayerWidgetPositionSpace, *ArabicLang);
             PrayerEdit(sizeofPrayerEdit,0,0);
             TodayIslamicEvent(sizeofIslamicEvent,posx,sizeofIslamicEvent.height()-75);

             int x=0;
             int y=ScreenSize1.height();
             HadithQuran(x,y);
              //  PrayerTimeVisible=false;
             PrayerFajerAdjustPlus->setVisible(false);
             PrayerFajerAdjustMinus->setVisible(false);
             PrayerSharouqAdjustPlus->setVisible(false);
             PrayerSharouqAdjustMinus->setVisible(false);
             PrayerDhuhrAdjustPlus->setVisible(false);
             PrayerDhuhrAdjustMinus->setVisible(false);
             PrayerAsrAdjustPlus->setVisible(false);
             PrayerAsrAdjustMinus->setVisible(false);
             PrayerMagribAdjustPlus->setVisible(false);
             PrayerMagribAdjustMinus->setVisible(false);
             PrayerIshaAdjustPlus->setVisible(false);
             PrayerIshaAdjustMinus->setVisible(false);
             FajerEditLabel->setVisible(false);
             ShrouqEditLabel->setVisible(false);
             DhuhrEditLabel->setVisible(false);
             AsrEditLabel->setVisible(false);
             MagribEditLabel->setVisible(false);
             IshaEditLabel->setVisible(false);
             HijriPlus->setVisible(false);
             HijriMinus->setVisible(false);
             HijriEditLabel->setVisible(false);
            // HijriLabel->setVisible(false);

            // FajerEditLabel->setText(QVariant(*addedTimeFajer).toString());
          //   ShrouqEditLabel->setText(QVariant(*addedTimeShrouq).toString());
          //   DhuhrEditLabel->setText(QVariant(*addedTimeDhuhr).toString());
          //   AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
//             MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
           //  IshaEditLabel->setText(QVariant(*addedTimeIsha).toString());



             Time->setText("Hijri Editing");
             EditTimePrayers->setText("Editing Prayers Time");
             EditTimeIqamah->setText("Editing Iqamah Time");
             English->setText("English");
             Arabic->setText("Arabic");
             AddingMessageMenu->setTitle("Add Message");
             PrayersMenu->setTitle("Prayers Time");
             TimeMenu->setTitle("Hijri Date");
             Language->setTitle("Language");
             InterfaceThema->setTitle("Thema");
             SettingButton->setText("Settings");
             FactoryResetMenu->setTitle("Configuration");
             BlackThema->setText("Black Thema");
             WhiteThema->setText("White Thema");
             AddMessage->setText("Add Message");
             FactoryReset->setText("Factory Reset");
             DefaultConfig->setText("Default Configuration");
             AzanSettings->setTitle("Azan Settings");
             AzanSettings_azan->setTitle("Prayers");
             AzanSettings_Mothen->setTitle("Mozthen");
             Fajer_azan->setText("Fajer");
             Dhuhr_azan->setText("Dhuhr");
             Asr_azan->setText("Asr");
             Magrib_azan->setText("Magrib");
             Isha_azan->setText("Isha");

             Sleep_None->setText("Always");
             Sleep_Default->setText("By Azan");
             Sleeping_Mode->setTitle("Screen Activation");
             wireless->setText("Connect to wireless");
             database->setText("Sync Database");

             reboot->setText("Reboot");
             shutdown->setText("Shutdown");

         }
}
if(UPDATE== UPDATE::AZAN | UPDATE==UPDATE::ALL){
    a_fajer=Settings.ReadSettings("Azan","fajer").toBool();
    a_dhuhr=Settings.ReadSettings("Azan","dhuhr").toBool();
    a_asr=Settings.ReadSettings("Azan","asr").toBool();
    a_mgrib=Settings.ReadSettings("Azan","mgrib").toBool();
    a_isha=Settings.ReadSettings("Azan","isha").toBool();

    Fajer_azan->setChecked(a_fajer);

  Dhuhr_azan->setChecked(a_dhuhr);
  Asr_azan->setChecked(a_asr);
  Magrib_azan->setChecked(a_mgrib);
  Isha_azan->setChecked(a_isha);

}
if(UPDATE== UPDATE::SLEEP | UPDATE==UPDATE::ALL){
   sleep_no=Settings.ReadSettings("Sleep_Mode","None").toBool();
   sleep_def=Settings.ReadSettings("Sleep_Mode","Default").toBool();
    Sleep_None->setChecked(sleep_no);
   Sleep_Default->setChecked(sleep_def);

}

if(UPDATE== UPDATE::VOLUME | UPDATE==UPDATE::ALL){
   volume=Settings.ReadSettings("volume","volume").toInt();


}

if(IslamicEventContent->text()=="")
    IslamicEventContent->setVisible(false);
if(IslamicEventTitle->text()=="")
    IslamicEventTitle->setVisible(false);

}
void MainWindow::iqamahMessage(){
    if(*currentPrayerPtr=="Fajer"){
        iqamahFajerCounter--;
      iqamahMessageLabel->setText("الوقت المتبقي لصلاة الفجر \n  Time remainning for "+*currentPrayerPtr+" \n "+"دقيقة"+QVariant(iqamahFajerCounter).toString()+"\n دقيقة"+" Minutes\n");
      if(iqamahFajerCounter==0 || iqamahFajerCounter <= 0){
          timer1->stop();
          timer2->start(10);
          iqamahTimer->stop();

          }
         }

     if(*currentPrayerPtr=="Dhuhr"){
    iqamahDhuhrCounter--;
    if(QDate::currentDate().dayOfWeek()==5)
        iqamahMessageLabel->setText("الوقت المتبقي لصلاة الجمعة \n Time remainning for Jumma \n "+QVariant(iqamahDhuhrCounter).toString()+"\n دقيقة"+" Minutes\n");
    else
      iqamahMessageLabel->setText("الوقت المتبقي لصلاة الظهر \n Time remainning for "+*currentPrayerPtr+" \n "+QVariant(iqamahDhuhrCounter).toString()+"\n دقيقة"+" Minutes\n");
      if(iqamahDhuhrCounter==0 || iqamahDhuhrCounter <= 0){
          timer1->stop();
          timer2->start(10);
          iqamahTimer->stop();


          }
         }

     if(*currentPrayerPtr=="Asr"){
        qDebug()<<iqamahAsrCounter;
    iqamahAsrCounter--;
      iqamahMessageLabel->setText("الوقت المتبقي لاقامة صلاة العصر \n Time remainning for "+*currentPrayerPtr+"\n"+QVariant(iqamahAsrCounter).toString()+"\n دقيقة"+" Minutes\n");
      if(iqamahAsrCounter==0 || iqamahAsrCounter <= 0){
          timer1->stop();
          timer2->start(10);
          iqamahTimer->stop();

          }
         }



     if(*currentPrayerPtr=="Magrib"){
        qDebug()<<iqamahMagribCounter;
    iqamahMagribCounter--;
      iqamahMessageLabel->setText("الوقت المتبقي لصلاة المغرب \n Time remainning for "+*currentPrayerPtr+" \n "+QVariant(iqamahMagribCounter).toString()+"\n دقيقة"+" Minutes\n");
      if(iqamahMagribCounter<=0 || iqamahMagribCounter == 0){
          timer1->stop();
          timer2->start(10);
          iqamahTimer->stop();

          }
         }



     if(*currentPrayerPtr=="Isha"){
        qDebug()<<iqamahIshaCounter;
    iqamahIshaCounter--;
      iqamahMessageLabel->setText("الوقت المتبقي لصلاة العشاء \n Time remainning for "+*currentPrayerPtr+" \n"+QVariant(iqamahIshaCounter).toString()+"\n دقيقة"+" Minutes\n");
      if(iqamahIshaCounter==0 || iqamahIshaCounter <=0 ){
          timer1->stop();
          timer2->start(10);
          iqamahTimer->stop();

          }
         }




    }
void MainWindow::ChangeInterfaceLanguageArabic(){
 ThemaChange=!ThemaChange;
    Settings.StoreSettings("InterfaceLanguage","Arabic",true);
    v_ArabicLang=Settings.ReadSettings("InterfaceLanguage","Arabic").toBool();
    RefreshTimes(UPDATE::LANG);
    UpdateHadithQuranInterface();



}
void MainWindow::ChangeInterfaceLanguageEnglish(){
 ThemaChange=!ThemaChange;

    Settings.StoreSettings("InterfaceLanguage","Arabic",false);
    v_ArabicLang=Settings.ReadSettings("InterfaceLanguage","Arabic").toBool();
    RefreshTimes(UPDATE::LANG);
    UpdateHadithQuranInterface();



}
void MainWindow::ChangeInterfaceThemaWhite(){
    ThemaChange=true;
    Settings.StoreSettings("appreance","Thema","White");
    CssFile=StyleSheetFile.ParsingCssFile(ApplicationPath+"/StyleSheet/WhiteThema.css");
    SettingMenu->setProperty("Type",15);
    SettingMenu->style()->polish(this);
    SettingMenu->style()->unpolish(this);
    SettingMenu->setStyleSheet(CssFile);
    PrayersMenu->setProperty("Type",15);
    PrayersMenu->style()->polish(this);
    PrayersMenu->style()->unpolish(this);
    PrayersMenu->setStyleSheet(CssFile);
    TimeMenu->setProperty("Type",15);
    TimeMenu->style()->polish(this);
    TimeMenu->style()->unpolish(this);
    TimeMenu->setStyleSheet(CssFile);
    Language->setProperty("Type",15);
    Language->style()->polish(this);
    Language->style()->unpolish(this);
    Language->setStyleSheet(CssFile);
    InterfaceThema->setProperty("Type",15);
    InterfaceThema->style()->polish(this);
    InterfaceThema->style()->unpolish(this);
    InterfaceThema->setStyleSheet(CssFile);
    FactoryResetMenu->setProperty("Type",15);
    FactoryResetMenu->style()->polish(this);
    FactoryResetMenu->style()->unpolish(this);
    FactoryResetMenu->setStyleSheet(CssFile);
    AddingMessageMenu->setProperty("Type",15);
    AddingMessageMenu->style()->polish(this);
    AddingMessageMenu->style()->unpolish(this);
    AddingMessageMenu->setStyleSheet(CssFile);
    AzanSettings_azan->setProperty("Type",15);
    AzanSettings_azan->style()->polish(this);
    AzanSettings_azan->style()->unpolish(this);
    AzanSettings_azan->setStyleSheet(CssFile);
    AzanSettings_Mothen->setProperty("Type",15);
    AzanSettings_Mothen->style()->polish(this);
    AzanSettings_Mothen->style()->unpolish(this);
    AzanSettings_Mothen->setStyleSheet(CssFile);

            AzanSettings->setProperty("Type",15);
            AzanSettings->style()->polish(this);
            AzanSettings->style()->unpolish(this);
            AzanSettings->setStyleSheet(CssFile);
            Sleeping_Mode->setProperty("Type",15);
            Sleeping_Mode->style()->polish(this);
            Sleeping_Mode->style()->unpolish(this);
            Sleeping_Mode->setStyleSheet(CssFile);





    RefreshTimes(UPDATE::THEME);
       }
void MainWindow::ChangeInterfaceThemaBlack(){
     ThemaChange=true;
     Settings.StoreSettings("appreance","Thema","Black");
    CssFile=StyleSheetFile.ParsingCssFile(ApplicationPath+"/StyleSheet/BlackThema.css");
    SettingMenu->setProperty("Type",15);
    SettingMenu->style()->polish(this);
    SettingMenu->style()->unpolish(this);
    SettingMenu->setStyleSheet(CssFile);
    PrayersMenu->setProperty("Type",15);
    PrayersMenu->style()->polish(this);
    PrayersMenu->style()->unpolish(this);
    PrayersMenu->setStyleSheet(CssFile);
    TimeMenu->setProperty("Type",15);
    TimeMenu->style()->polish(this);
    TimeMenu->style()->unpolish(this);
    TimeMenu->setStyleSheet(CssFile);
    Language->setProperty("Type",15);
    Language->style()->polish(this);
    Language->style()->unpolish(this);
    Language->setStyleSheet(CssFile);
    InterfaceThema->setProperty("Type",15);
    InterfaceThema->style()->polish(this);
    InterfaceThema->style()->unpolish(this);
    InterfaceThema->setStyleSheet(CssFile);
    FactoryResetMenu->setProperty("Type",15);
    FactoryResetMenu->style()->polish(this);
    FactoryResetMenu->style()->unpolish(this);
    FactoryResetMenu->setStyleSheet(CssFile);
    AddingMessageMenu->setProperty("Type",15);
    AddingMessageMenu->style()->polish(this);
    AddingMessageMenu->style()->unpolish(this);
    AddingMessageMenu->setStyleSheet(CssFile);
    AzanSettings_azan->setProperty("Type",15);
    AzanSettings_azan->style()->polish(this);
    AzanSettings_azan->style()->unpolish(this);
    AzanSettings_azan->setStyleSheet(CssFile);
    AzanSettings_Mothen->setProperty("Type",15);
    AzanSettings_Mothen->style()->polish(this);
    AzanSettings_Mothen->style()->unpolish(this);
    AzanSettings_Mothen->setStyleSheet(CssFile);

            AzanSettings->setProperty("Type",15);
            AzanSettings->style()->polish(this);
            AzanSettings->style()->unpolish(this);
            AzanSettings->setStyleSheet(CssFile);

            Sleeping_Mode->setProperty("Type",15);
            Sleeping_Mode->style()->polish(this);
            Sleeping_Mode->style()->unpolish(this);
            Sleeping_Mode->setStyleSheet(CssFile);


    RefreshTimes(UPDATE::THEME);

}
void MainWindow::ShowEditingHijriDate(){
    HijriEditShow=!HijriEditShow;
    HijriEditLabel->setVisible(HijriEditShow);
    HijriPlus->setVisible(HijriEditShow);
    HijriMinus->setVisible(HijriEditShow);


}
void MainWindow::HijriPushButtonIncrease(){


    HijriAddedDays_v++;
    HijriEditLabel->setText(QVariant(*HijriAddedDays).toString());
    Settings.StoreSettings("Hijri","AddedDays",*HijriAddedDays);
    int day = QDate::currentDate().day();
    int month = QDate::currentDate().month();
    int year = QDate::currentDate().year();
    QString date = HijriDate.PrintCalender(day+HijriAddedDays_v,month,year,0);
    HijriLabel->setText(date);




}
void MainWindow::HijriPushButtonDecrease(){
    HijriAddedDays_v--;
    HijriEditLabel->setText(QVariant(*HijriAddedDays).toString());
    Settings.StoreSettings("Hijri","AddedDays",*HijriAddedDays);
    int day = QDate::currentDate().day();
    int month = QDate::currentDate().month();
    int year = QDate::currentDate().year();
    QString date = HijriDate.PrintCalender(day+HijriAddedDays_v,month,year,0);
    qDebug()<<date;
    HijriLabel->setText(date);

}
void MainWindow::UpdateHadithQuranInterface(){



     HadithOrQuran = !HadithOrQuran ;
    int Hadith_Cate2=0;
    int Quran_Cate2 = 0;
    int Number = rand() % 5 + 1;

    Query = Database.SelectIslamicEvent();
    Query.first();
    QString Event = Query.value(0).toString();
    QString IslamicEvent = Query.value(1).toString();
    qDebug()<<"First Number : "<<Event<<"second :"<< Number <<"Hadith or Quran"<<HadithOrQuran ;

    int Class = Query.value(2).toInt();
    if(Class == 0){
       Hadith_Cate2 = rand() % 23 + 1 ;
       Quran_Cate2 = rand() % 28 + 1;
      }else {
       Hadith_Cate2 = 0;
       Quran_Cate2 = 0;

       }

           qDebug()<<"Islamic Event: "<<IslamicEvent<<"Event = "<<Event<<"Calss ="<<Class << "Hadith Number ="<<Hadith_Cate2;


          IslamicEventTitle->setText(Event);
          IslamicEventContent->setText(IslamicEvent);
          if(IslamicEventContent->text()=="")
              IslamicEventContent->setVisible(false);
          if(IslamicEventTitle->text()=="")
              IslamicEventTitle->setVisible(false);

     QSqlQuery Hadith;
     QSqlQuery Quran;
     QString ArabicHadithTextTab="حديث اليوم : قال رسول الله";
     QString EnglishHadithTextTab="Hadith'Today : Prophet(PBUH) said";
     QString ArabicQuranTextTab= "اية اليوم";
     QString EnglishQuranTextTab="Aya's Today";

    if(HadithOrQuran){
        Hadith= Database.Hadith(Class,Hadith_Cate2,Number);

        Hadith.first();
        QString ArabicText1= Hadith.value(0).toString();
        QString EnglishText1= Hadith.value(1).toString();
        QString Narrator = Hadith.value(2).toString();
        if(Narrator=="1"){
            qDebug()<<"Narrator :"<<Narrator;



        }
   //     HadithQuranLabel->setStyleSheet("background-color: rgb(0, 0, 0 , 100); border-bottom-left-radius:15px; border-top-left-radius:15px;border-top-right-radius:15px;border-bottom-right-radius:15px;color: rgb(255, 255, 255);");

        if(*ArabicLang==true){
        HadithQuranLabel->setText(ArabicText1);
        HadithQuranTabLabel->setText(ArabicHadithTextTab);
        Time->setText("تعديل التاريخ الهجري");
        EditTimePrayers->setText("تعديل اوقات الصلاة");
        EditTimeIqamah->setText("تعديل اوقات الاقامة");
        English->setText("انكليزي");
        Arabic->setText("عربي");
        AddingMessageMenu->setTitle("اضافة رسالة");
        PrayersMenu->setTitle("اوقات الصلاة");
        TimeMenu->setTitle("هجري");
        Language->setTitle("اللغة");
        InterfaceThema->setTitle("المظهر");
        SettingButton->setText("الاعدادات");
        SettingMenu->setTitle("الاعدادات");
        FactoryResetMenu->setTitle("استعادة الاعدادات الافتراضية");
        BlackThema->setText("مظهر الاسود");
        WhiteThema->setText("مظهر الابيض");
        AddMessage->setText("اضافة رسالة");
        FactoryReset->setText("اعادة ضبط المصنع");
        DefaultConfig->setText("الاعدادات الافتراضية");


        }else
        {
            HadithQuranTabLabel->setText(EnglishHadithTextTab);

            HadithQuranLabel->setText(EnglishText1);

            Time->setText("Hijri Editing");
            EditTimePrayers->setText("Editing Prayers Time");
            EditTimeIqamah->setText("Editing Iqamah Time");
            English->setText("English");
            Arabic->setText("Arabic");
            AddingMessageMenu->setTitle("Add Message");
            PrayersMenu->setTitle("Prayers Time");
            TimeMenu->setTitle("Hijri Date");
            Language->setTitle("Language");
            InterfaceThema->setTitle("Thema");
            SettingButton->setText("Settings");
            SettingMenu->setTitle("الاعدادات");
            FactoryResetMenu->setTitle("Configuration");
            BlackThema->setText("Black Thema");
            WhiteThema->setText("White Thema");
            AddMessage->setText("Add Message");
            FactoryReset->setText("Factory Reset");
            DefaultConfig->setText("Default Configuration");
        }}
        else if(!HadithOrQuran){
        Quran = Database.Quran(Class,Quran_Cate2,Number);


        Quran.first();
            QString ArabicText= Quran.value(0).toString();
            QString EnglishText = Quran.value(1).toString();
            if(*ArabicLang==true){
            HadithQuranLabel->setText(ArabicText);
            HadithQuranTabLabel->setText(ArabicQuranTextTab);

            }
                            else{            {
                HadithQuranLabel->setText(EnglishText);
                HadithQuranTabLabel->setText(EnglishQuranTextTab);

            }




    }


}
}
void MainWindow::AddingMessageSlot(){
    AddingMessageEvent->setGeometry(QRect((ScreenSize1.width()/2)-200,10,400,200));
    AddingMessageEvent->setProperty("Type",1);
    AddingMessageEvent->raise();
    AddingMessageEvent->setPlaceholderText("يمكنك وضع الرسالة هنا \n Please Enter Your Message here ");
    AddingMessageEvent->style()->polish(this);
    AddingMessageEvent->style()->unpolish(this);
    AddingMessageEvent->setWordWrapMode(QTextOption::WordWrap);
    AddingMessageEvent->setAlignment(Qt::AlignHCenter);
    AddingMessageEvent->setStyleSheet(CssFile);
    AddingMessageEvent->show();
    SaveMessage->setGeometry(QRect(AddingMessageEvent->pos().x(),AddingMessageEvent->pos().y()+205,50,20));
    SaveMessage->setProperty("Type",18);
    SaveMessage->setText("Save");
    SaveMessage->style()->polish(this);
    SaveMessage->style()->unpolish(this);
    SaveMessage->setStyleSheet(CssFile);
    SaveMessage->raise();
    SaveMessage->show();



}
void MainWindow::on_SaveMessage(){

    IslamicEventContent->setText(AddingMessageEvent->toPlainText());
     if(IslamicEventContent->text()!="")
         IslamicEventContent->setVisible(true);
     else {
           IslamicEventContent->setVisible(false);
     }
    SaveMessage->setVisible(false);
    AddingMessageEvent->setVisible(false);


}
void MainWindow::DeletingSettingsFile(){

    system("rm Settings.ini");

}
void MainWindow::DefaultSettings(){

    system("cp -rf DefaultSettings.ini Settings.ini");


}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(event->button( ) == Qt::RightButton){
        cout << "Left Button Clicked." << endl;
        PrayerFajerAdjustPlus->setVisible(false);
        PrayerFajerAdjustMinus->setVisible(false);
        PrayerSharouqAdjustPlus->setVisible(false);
        PrayerSharouqAdjustMinus->setVisible(false);
        PrayerDhuhrAdjustPlus->setVisible(false);
        PrayerDhuhrAdjustMinus->setVisible(false);
        PrayerAsrAdjustPlus->setVisible(false);
        PrayerAsrAdjustMinus->setVisible(false);
        PrayerMagribAdjustPlus->setVisible(false);
        PrayerMagribAdjustMinus->setVisible(false);
        PrayerIshaAdjustPlus->setVisible(false);
        PrayerIshaAdjustMinus->setVisible(false);
        FajerEditLabel->setVisible(false);
        ShrouqEditLabel->setVisible(false);
        DhuhrEditLabel->setVisible(false);
        AsrEditLabel->setVisible(false);
        MagribEditLabel->setVisible(false);
        IshaEditLabel->setVisible(false);
        HijriPlus->setVisible(false);
        HijriMinus->setVisible(false);
        HijriEditLabel->setVisible(false);
        progress->hide();



    }
}
MainWindow::~MainWindow()
{
    delete addedTimeFajer;
    delete addedTimeShrouq;
    delete addedTimeDhuhr;
    delete addedTimeAsr;
    delete addedTimeMagrib;
    delete addedTimeIsha;
    delete index;
    delete ui;
    delete ArabicLang;
}
void MainWindow::newConnection()
{

    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();
    QString IpAddress=socket->peerAddress().toString();
    QString Address=IpAddress.remove("::ffff:");
    qDebug()<<Address;
    QString mac=getMacAddress();
    //socket->write("Hello client\r\n");
    //socket->flush();


    //delete mgr;

    if(socket->bytesAvailable()<=0){
        qDebug() << "there is no data: ";


    }

    socket->waitForReadyRead();

        qDebug() << socket->bytesAvailable();

        const int MaxLength = 2048;
        char buffer[MaxLength + 1];

        qint64 byteCount = socket->read(buffer, MaxLength);
        buffer[byteCount] = 0;

        QString Command = QVariant(buffer).toString();
        QRegExp rx("(\\ )"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
        QStringList query = Command.split(rx);

       foreach (QString item, query)
           qDebug()<<"item"<<item;


       if(query[0]=="PrayerTime"){
           *addedTimeFajer=query[1].toInt();
           FajerEditLabel->setText(QVariant(*addedTimeFajer).toString());
           Settings.StoreSettings("PrayerAdjustment","AddedTimeFajer",*addedTimeFajer);
           *addedTimeDhuhr=query[2].toInt();
           DhuhrEditLabel->setText(QVariant(*addedTimeDhuhr).toString());
           Settings.StoreSettings("PrayerAdjustment","AddedTimeDhuhr",*addedTimeDhuhr);
           *addedTimeAsr=query[3].toInt();
           AsrEditLabel->setText(QVariant(*addedTimeAsr).toString());
           Settings.StoreSettings("PrayerAdjustment","AddedTimeAsr",*addedTimeAsr);
           *addedTimeMagrib=query[4].toInt();
           MagribEditLabel->setText(QVariant(*addedTimeMagrib).toString());
           Settings.StoreSettings("PrayerAdjustment","AddedTimeMagrib",*addedTimeMagrib);
           *addedTimeIsha=query[5].toInt();
           IshaEditLabel->setText(QVariant(*addedTimeIsha).toString()); //QVariant(*addedTimeIsha).toString()
           Settings.StoreSettings("PrayerAdjustment","AddedTimeIsha",*addedTimeIsha);
           *iqamahTimeFajer=query[6].toInt();
           Settings.StoreSettings("iqamahAdjustment","iqamahTimeFajer",*iqamahTimeFajer);
           *iqamahTimeIsha=query[10].toInt();

           Settings.StoreSettings("iqamahAdjustment","iqamahTimeIsha",*iqamahTimeIsha);
           *iqamahTimeMagrib=query[9].toInt();

           Settings.StoreSettings("iqamahAdjustment","iqamahTimeMagrib",*iqamahTimeMagrib);
           *iqamahTimeAsr=query[8].toInt();

           Settings.StoreSettings("iqamahAdjustment","iqamahTimeAsr",*iqamahTimeAsr);
           *iqamahTimeDhuhr=query[7].toInt();

           Settings.StoreSettings("iqamahAdjustment","iqamahTimeDhuhr",*iqamahTimeDhuhr);

           RefreshTimes(UPDATE::PRAYER_ADD);
           RefreshTimes(UPDATE::IQAMAH);


       }


        if(Command=="Arabic"){
        ChangeInterfaceLanguageArabic();
        qDebug() << buffer<<Command;

        }
        else if (Command=="English") {
        ChangeInterfaceLanguageEnglish();        }
        else if (Command=="White"){
            ChangeInterfaceThemaWhite();
        }
       else  if (Command=="Black"){
            ChangeInterfaceThemaBlack();
        }

        else if(Command=="muted"){
            Settings.StoreSettings("volume","volume",0);
            RefreshTimes(VOLUME);

            player->setVolume(volume);

                }

       else  if(Command=="del_msg"){
            IslamicEventContent->setVisible(false);
            IslamicEventContent->setText("");
        } else if(query[0]=="create_msg"){

            QString text="";
            for (int i=1;i<query.size();i++) {

                text+=" "+query[i];
            }
             IslamicEventContent->setText(text);
             IslamicEventContent->setVisible(true);

             qDebug() <<Command;

        }else if(query[0]=="Hijri"){

            *HijriAddedDays= QVariant(query[1]).toInt();
            HijriEditLabel->setText(QVariant(*HijriAddedDays).toString());
            Settings.StoreSettings("Hijri","AddedDays",*HijriAddedDays);
            int day = QDate::currentDate().day();
            int month = QDate::currentDate().month();
            int year = QDate::currentDate().year();
            QString date = HijriDate.PrintCalender(day+HijriAddedDays_v,month,year,0);
            HijriLabel->setText(date);
        }else if(query[0]=="reset"){

            system("rm Settings.ini");


        }else if(query[0]=="default"){
            system("cp -rf DefaultSettings.ini Settings.ini");


        }else if(query[0]=="sleep_no"){
            Store_Sleep_None();



        }else if(query[0]=="sleep_def"){
            Store_Sleep_Def();
        }else if(query[0]=="fajer"){
            Store_Fajer_azan();
        }else if(query[0]=="dhuhr"){
            Store_Dhuhr_azan();
        }else if(query[0]=="asr"){
            Store_Asr_azan();
        }else if(query[0]=="magrib"){
            Store_Magrib_azan();
        }else if(query[0]=="isha"){
            Store_Isha_azan();
        }
        else if(query[0]=="sync"){

            // server1 = new QTcpServer();

                //server1->connectToHost("192.168.0.102",39440, QIODevice::ReadWrite);
            QString str1 = "python "+ApplicationPath+"/Sender.py "+IpAddress;
             QByteArray ba = str1.toLocal8Bit();
             const char *c_str2 = ba.data();
             printf("str2: %s", c_str2);

                system(c_str2);
}

        else if(query[0]=="volume"){
            Settings.StoreSettings("volume","volume",query[1].toInt());
            RefreshTimes(VOLUME);
            player->setVolume(query[1].toInt());
        }else if(query[0]=="reboot"){

            system("sudo reboot");

        }

        QString currentDate=QDate::currentDate().toString("yyyy-MM-dd");
        QString City=Settings.ReadSettings("GPS_Information","City").toString();
        QString Country=Settings.ReadSettings("GPS_Information","Country").toString();
        QString name=Settings.ReadSettings("MosqueInformation","Name").toString();
        QString street=Settings.ReadSettings("MosqueInformation","Street").toString();
        QString house_no=Settings.ReadSettings("MosqueInformation","house_no").toString();
        QString zip=Settings.ReadSettings("MosqueInformation","zip").toString();





        QString Method=Settings.ReadSettings("PrayerSettings","Method").toString();
        QString email=Settings.ReadSettings("MosqueInformation","Email").toString();
        QString asr_method=Settings.ReadSettings("PrayerSettings","AsrMethod").toString();
        QString time_zone=Settings.ReadSettings("LocalSettings","TimeZone").toString();



        mgr->get(QNetworkRequest(QUrl("https://mymosque2019.000webhostapp.com/trial/api.php?client=app&cmd=reg_mosque&mac="+mac+"&name="+name+"&country="+Country+"&city="+City+"&street="+street+"&house_no="+house_no+"&zip="+zip+"&status=1&ip=192&method="+Method+"&code=&date="+currentDate+"&email="+email+"&time_zone="+time_zone+"&asr_method="+asr_method+"")));


         qDebug()<<"it works"<<"https://mymosque2019.000webhostapp.com/trial/api.php?client=app&cmd=reg_mosque&mac="+mac+"&name="+name+"&country="+Country+"&city="+City+"&street="+street+"&house_no="+house_no+"&zip="+zip+"&status=1&ip=192&method="+Method+"&code=&date="+currentDate+"&email="+email+"&time_zone="+time_zone+"&asr_method="+asr_method+""<<endl;
        mgr->get(QNetworkRequest(QUrl("https://mymosque2019.000webhostapp.com/trial/api.php?client=app&cmd=time_diff&mac="+mac+"&fajer="+QVariant(addedTimeFajer_v).toString()+"&sharouq="+QVariant(addedTimeShrouq_v).toString()+"&dhuhr="+QVariant(addedTimeDhuhr_v).toString()+"&asr="+QVariant(addedTimeAsr_v).toString()+"&magrib="+QVariant(addedTimeMagrib_v).toString()+"&isha="+QVariant(addedTimeIsha_v).toString()+"&i_fajer="+QVariant(iqamahTimeFajer_v).toString()+"&i_sharouq="+QVariant(iqamahTimeShrouq_v).toString()+"&i_dhuhr="+QVariant(iqamahTimeDhuhr_v).toString()+"&i_asr="+QVariant(iqamahTimeAsr_v).toString()+"&i_magrib="+QVariant(iqamahTimeMagrib_v).toString()+"&i_isha="+QVariant(iqamahTimeIsha_v).toString()+"&update_date="+currentDate+"")));
        qDebug()<<"it works"<<mac<<endl;


    //socket->waitForBytesWritten(3000);

  //  socket->close();
}
void MainWindow::Store_Fajer_azan(){

    Settings.StoreSettings("Azan","fajer",!a_fajer);
    RefreshTimes(AZAN);



}
void MainWindow::Store_Dhuhr_azan(){
Settings.StoreSettings("Azan","dhuhr",!a_dhuhr);
RefreshTimes(AZAN);
}
void MainWindow::Store_Asr_azan(){
    Settings.StoreSettings("Azan","asr",!a_asr);
RefreshTimes(AZAN);
}
void MainWindow::Store_Magrib_azan(){
    Settings.StoreSettings("Azan","mgrib",!a_mgrib);
    RefreshTimes(AZAN);
}
void MainWindow::Store_Isha_azan(){
    Settings.StoreSettings("Azan","isha",!a_isha);
RefreshTimes(AZAN);
}
void MainWindow::Store_Sleep_None(){
    Settings.StoreSettings("Sleep_Mode","None",!sleep_no);
RefreshTimes(SLEEP);
}
void MainWindow::Store_Sleep_Def(){
    Settings.StoreSettings("Sleep_Mode","Default",!sleep_def);
RefreshTimes(SLEEP);
}
void MainWindow::sendMessage(QString msgToSend){
QByteArray l_vDataToBeSent;
QDataStream l_vStream(&l_vDataToBeSent, QIODevice::WriteOnly);
l_vStream.setByteOrder(QDataStream::LittleEndian);
l_vStream << msgToSend.length();
l_vDataToBeSent.append(msgToSend);
//char* ch= msgToSend.toStdString().c_str();
l_vDataToBeSent = msgToSend.toUtf8().toBase64();

server1->write(l_vDataToBeSent.data(),l_vDataToBeSent.size());
}
void  MainWindow::connectToHost(QString hostname, int port){
    if(!server1)
{
    server1 = new QTcpSocket(this);
    server1->setSocketOption(QAbstractSocket::KeepAliveOption,1);
}
connect(server1,SIGNAL(readyRead()),SLOT(readSocketData()),Qt::UniqueConnection);
connect(server1,SIGNAL(error(QAbstractSocket::SocketError)),SIGNAL(connectionError(QAbstractSocket::SocketError)),Qt::UniqueConnection);
connect(server1,SIGNAL(stateChanged(QAbstractSocket::SocketState)),SIGNAL(tcpSocketState(QAbstractSocket::SocketState)),Qt::UniqueConnection);
connect(server1,SIGNAL(disconnected()),SLOT(onConnectionTerminated()),Qt::UniqueConnection);
connect(server1,SIGNAL(connected()),SLOT(onConnectionEstablished()),Qt::UniqueConnection);

if(!(QAbstractSocket::ConnectedState == server1->state())){
    server1->connectToHost(hostname,port, QIODevice::ReadWrite);
}
}
void MainWindow::onfinish(QNetworkReply *rep)
{
    QByteArray bts = rep->readAll();
    QString str(bts);

}
QString MainWindow::getMacAddress()
{
    QString text;
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        text = interface.hardwareAddress();
    }
    return text;
}
void MainWindow::wirelss_function(){

    wirelesslog wireless;
    wireless.show();
    wireless.exec();

}
void MainWindow::sync_database(){


    QNetworkAccessManager nam;

    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply* reply=nam.get(req);
    QEventLoop loop;
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QString name=Settings.ReadSettings("MosqueInformation","Name").toString();


    if(reply->bytesAvailable()){
    QNetworkAccessManager *nam2= new QNetworkAccessManager(this);
    QObject::connect(nam2,SIGNAL(finished(QNetworkReply*)),this,SLOT(OnResult(QNetworkReply*)));
    QUrl url("https://mymosque2019.000webhostapp.com/trial/api.php?client=app&cmd=get_database&mosque_name="+name);

    nam2->get(QNetworkRequest(url));
    }else {
    QMessageBox::information(this,"info","You are not connected to the  internet");
    }
}
void MainWindow::OnResult(QNetworkReply *reply){
QString name=Settings.ReadSettings("MosqueInformation","Name").toString();
    if(reply->error()== QNetworkReply::NoError){
        QByteArray result= reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
        //qDebug()<<"test is working1"<<jsonResponse.toVariant();
       // QJson::Parser parser;
        //QJson::
        //bool ok;
        //QVariantMap result=parser.parse(jsonResponse,&ok).toMap();
        QJsonObject obj =   jsonResponse.object();
        //QJsonArray array = obj[name].toArray();
            QJsonValue jsonvalue= obj.value(name);
            QJsonArray array=jsonResponse.array();
        progress->show();
        progress->setText("Running");
        foreach (const QJsonValue & value, array){
            QString date=value.toObject().value("date").toString().remove('"');
            QString fajer=value.toObject().value("fajer").toString().remove('"');
            QString fajer_i=value.toObject().value("fajer_i").toString();
            QString sharouq=value.toObject().value("sharouq").toString();
            QString dhuhr=value.toObject().value("dhuhr").toString();
            QString dhuhr_i=value.toObject().value("dhuhr_i").toString();
            QString asr=value.toObject().value("asr").toString();
            QString asr_i=value.toObject().value("asr_i").toString();
            QString magrib=value.toObject().value("magrib").toString();
            QString magrib_i=value.toObject().value("magrib_i").toString();
            QString isha=value.toObject().value("isha").toString();
            QString isha_i=value.toObject().value("isha_i").toString();
            QString friday_1=value.toObject().value("friday_1").toString();
            QString friday_2=value.toObject().value("friday_2").toString();

            qDebug()<<"Value fajer ="<<date<<fajer<<fajer_i<<sharouq<<dhuhr<<dhuhr_i<<asr<<asr_i<<magrib<<magrib_i<<isha<<isha_i<<friday_1<<friday_2;

            Database.insert_database_method(date,fajer,fajer_i, sharouq,  dhuhr,  dhuhr_i,  asr,  asr_i,
                                             magrib,  magrib_i,  isha,  isha_i,  friday_1,  friday_2 );
            //qDebug()<<"test is working1a"<<value.toString();
        }

        RefreshTimes(UPDATE::ALL);

        progress->setText("Done");

    }
}
void MainWindow::reboot_slot(){

    system("sudo reboot");

}
void MainWindow::shutdown_slot(){
    system("sudo shutdown now");
}


void MainWindow::resolutionChange(QAction *action){
    qDebug()<<" Data " <<action->data();
    int index= action->data().toInt();
    qDebug()<<" Inside resolution fucntion "<<index;
    QString command="xrandr -s "+lines[index];
    qDebug()<<command;
    QByteArray byte_array = command.toLocal8Bit();
    const char *system_command = byte_array.data();
    system(system_command);
    reboot_slot();

}

void MainWindow::update_slot()
{
    this->close();
    qDebug()<<"return file"<<std::system("Updater");
}
