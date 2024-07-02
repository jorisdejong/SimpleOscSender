#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible( ipEditor );
	ipEditor.setText( "127.0.0.1" );

	addAndMakeVisible( portEditor );
	portEditor.setText( "3334" );

	sender.connect( "127.0.0.1", 3334 );

	addAndMakeVisible( addressEditor );
	addressEditor.setText( "/test/address" );

	addAndMakeVisible( intSlider );
	intSlider.setSliderStyle( juce::Slider::SliderStyle::IncDecButtons );
	intSlider.setRange( { -1000.0, 1000.0 }, 1.0 );
	intSlider.onValueChange = [ this ]
		{
			sender.sendToIPAddress( 
				ipEditor.getText(), 
				portEditor.getText().getIntValue(), 
				juce::OSCMessage(
					addressEditor.getText(),
					int( intSlider.getValue() ) 
				) 
			);
		};

	setSize( 600, 400 );
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint( juce::Graphics& g )
{
	g.fillAll( getLookAndFeel().findColour( juce::ResizableWindow::backgroundColourId ) );
}

void MainComponent::resized()
{
	auto bounds = getLocalBounds();
	bounds.reduce( 10, 10 );

	int rowHeight = 25; 

	auto strip = bounds.removeFromTop( rowHeight );
	ipEditor.setBounds( strip.removeFromLeft( 120 ) );
	portEditor.setBounds( strip.removeFromLeft( 80 ) );
	addressEditor.setBounds( bounds.removeFromTop( rowHeight ) );

	bounds.removeFromTop( rowHeight );

	intSlider.setBounds( bounds.removeFromTop( rowHeight ).removeFromLeft( 200 ) );
}
