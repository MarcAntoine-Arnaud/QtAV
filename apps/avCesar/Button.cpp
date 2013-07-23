#include "Button.h"

Button::Button( QWidget *parent )
	: QToolButton( parent )
	, mState     ( NotFocused )
{
}

Button::Button( const QString& text, QWidget *parent )
	: QToolButton( parent )
	, mState( NotFocused )
{
}

Button::~Button()
{
}

Button::IconState Button::iconState() const
{
	return mState;
}

void Button::setIconState( IconState state, bool force )
{
	if( mState == state && ! force )
		return;
	mState = state;
	setIcon( iconForState( mState ) );
}

QIcon Button::iconForState( IconState state ) const
{
	if( ! mIcons.contains( state ) )
		return mIcons.begin().value();
	return mIcons.value( state );
}

void Button::setIconForState( IconState state, const QIcon &icon )
{
	mIcons.insert(state, icon);
}

void Button::setIconWithSates( const QPixmap &pixmap, IconState s1, IconState s2, IconState s3, IconState s4 )
{
	int  width  = pixmap.width();
	int  height = pixmap.height();
	int  count  = qMax( width, height ) / qMin( width, height );
	bool hor    = pixmap.height() < pixmap.width();
	QPoint dp;

	if( hor )
	{
		width /= count;
		dp.setX( width );
	}
	else
	{
		height /= count;
		dp.setY(height);
	}

	QRect rect( 0, 0, width, height );

	setIconForState( s1, pixmap.copy( rect ) );

	if( count > 1 )
	{
		rect.translate( dp );
		setIconForState( s2, pixmap.copy( rect ) );
		if( count > 2 )
		{
			rect.translate( dp );
			setIconForState( s3, pixmap.copy( rect ) );
			if( count > 3 )
			{
				rect.translate( dp );
				setIconForState( s4, pixmap.copy( rect ) );
			}
		}
	}
	setIconState( iconState(), true ); //TODO: other states set to existing icon
}

void Button::enterEvent( QEvent* e )
{
	QToolButton::enterEvent( e );

	if( mIcons.isEmpty() )
		return;

	setIconState(Focused);
	emit entered();
}

void Button::leaveEvent( QEvent* e )
{
	QToolButton::leaveEvent( e );

	if( mIcons.isEmpty() )
		return;

	setIconState( NotFocused );
	emit leaved();
}

void Button::mousePressEvent( QMouseEvent* e )
{
	QToolButton::mousePressEvent( e );

	if( mIcons.isEmpty() )
		return;

	setIconState( Pressed );
}

void Button::mouseReleaseEvent( QMouseEvent* e )
{
	QToolButton::mouseReleaseEvent( e );

	if( mIcons.isEmpty() )
		return;

	setIconState( Focused );
}
