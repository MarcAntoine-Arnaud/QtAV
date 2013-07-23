#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace QtAV {
class AudioOutput;
class AVPlayer;
class AVClock;
class VideoRenderer;
}

class QMenu;
class QTimeEdit;
class QVBoxLayout;
class QLabel;
class QPushButton;
class Button;
class Slider;


class MainWindow : public QWidget
{
	enum EShowControl
	{
		eShowControlCanHide = 0, // can hide
		eShowControlPlaying,     // show and playing
		eShowControlAlways       // always show(not playing)
	};

	Q_OBJECT
public:
	explicit MainWindow( QWidget *parent = 0 );
	~MainWindow();
	void enableAudio( bool yes = true );
	void setAudioOutput( QtAV::AudioOutput* );
	void setRenderer( QtAV::VideoRenderer* renderer );
	void play( const QString& name );

public slots:
	void openFile();
	void togglePlayPause();

signals:
	void ready();

private slots:
	void about();
	void help();
	void openUrl();
	void switchAspectRatio ( QAction* action);
	void setRepeat         ( QAction* action);
	void changeVO          ( QAction* action);
	void playOnlineVideo   ( QAction* action);
	void processPendingActions();
	void initPlayer();
	void setupUi();
	void onSpinBoxChanged( double v);
	void onStartPlay();
	void onStopPlay();
	void onPaused( bool p );
	void onSpeedChange( qreal speed );
	void seekToMSec( int msec );
	void seek();
	void capture();
	void showHideVolumeBar();
	void setVolume();
	void tryHideControlBar();
	void tryShowControlBar();

protected:
	virtual void resizeEvent ( QResizeEvent * );
	virtual void timerEvent  ( QTimerEvent  * );
	void mouseMoveEvent(QMouseEvent *e);

private:
	QVBoxLayout *mpPlayerLayout;

	QWidget* mpControl;
	QLabel*  mpCurrent;
	QLabel*  mpDuration;
	QLabel*  mpSpeed;
	Slider*  mpTimeSlider;
	Slider*  mpVolumeSlider;
	Button*  mpVolumeBtn;
	Button*  mpPlayPauseBtn;
	Button*  mpStopBtn;
	Button*  mpForwardBtn;
	Button*  mpBackwardBtn;
	Button*  mpOpenBtn;
	Button*  mpInfoBtn;
	Button*  mpMenuBtn;
	Button*  mpSetupBtn;
	Button*  mpCaptureBtn;
	QMenu*   mpMenu;
	QAction* mpVOAction;
	QAction* mpARAction; //remove mpVOAction if vo.id() is supported
	QAction* mpRepeatAction;

	QList<QAction*> mVOActions;

	QtAV::AVClock*       mpClock;
	QtAV::AVPlayer*      mpPlayer;
	QtAV::VideoRenderer* mpRenderer, *mpTempRenderer;

	QString mFile;
	QPixmap mPlayPixmap;
	QPixmap mPausePixmap;

	EShowControl mShowControl;
	int  mTimerId;

	bool mIsReady;
	bool mHasPendingPlay;
	bool mNullAO;
};

#endif
