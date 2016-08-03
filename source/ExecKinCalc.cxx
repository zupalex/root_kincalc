#include <TRint.h>
#include <TApplication.h>
#include <TVirtualX.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TRootEmbeddedCanvas.h>

#include "kinematic.h"

using std::string;

TGTextEntry* beamElLabel;
TGTextEntry* targetElLabel;
TGTextEntry* ejecElLabel;
TGTextEntry* recoilElLabel;

TGNumberEntryField* beamKeLabel;
TGNumberEntryField* targetKeLabel;
TGNumberEntryField* ejecKeLabel;
TGNumberEntryField* recoilKeLabel;

TGNumberEntryField* beamExLabel;
TGNumberEntryField* targetExLabel;
TGNumberEntryField* ejecExLabel;
TGNumberEntryField* recoilExLabel;

void RootKinCalc::OnClickCalcKin()
{
    RootKinCalc* kinCalc = new RootKinCalc();

    string beamStr, targetStr, ejecStr;

    beamStr = beamElLabel->GetText();
    targetStr = targetElLabel->GetText();
    ejecStr = ejecElLabel->GetText();

    if ( beamStr.empty() || targetStr.empty() || ejecStr.empty() ) return;

    float beamEk;
    float ejecEx, recEx;

    beamEk = beamKeLabel->GetNumber();
    ejecEx = ejecExLabel->GetNumber();
    recEx = recoilExLabel->GetNumber();

    kinCalc->GetReactionKinematic ( beamStr, targetStr, ejecStr, beamEk, ejecEx, recEx );
}

int main ( int argc, char *argv[] )
{
    // Create an interactive ROOT application
    TRint *theApp = new TRint ( "Rint", &argc, argv );

    TGMainFrame* controlFrame = new TGMainFrame ( gClient->GetRoot(), 2000, 2000 );
    controlFrame->SetWindowName ( "ROOT Kinematic Calculator" );
    controlFrame->SetName ( "ROOT Kinematic Calculator" );
//     controlFrame->SetBackgroundColor ( 0x4d004d );

//     controlFrame->Connect ( "Destroyed()", "GoddessCalib", sinstance(), "DeleteSInstance()" );

    // ------ Creating Main IF Frame ------ //

    TGCompositeFrame* mainIFFrame = new TGCompositeFrame ( controlFrame, 2000, 2000 );
    mainIFFrame->SetName ( "Main IF Frame" );
    mainIFFrame->SetLayoutManager ( new TGRowLayout ( mainIFFrame, 20 ) );

    // ------ Creating Reaction List Frame ------ //

    TGCompositeFrame* reacFrame = new TGCompositeFrame ( mainIFFrame, 2000, 2000 );
    reacFrame->SetName ( "Reaction List Frame" );
    reacFrame->SetLayoutManager ( new TGColumnLayout ( reacFrame, 20 ) );

    // ------ Creating Reaction List Selectable Menu ------ //

    TGLabel* reacListLabel = new TGLabel ( reacFrame, "Reactions List" );

    TGListBox *reacListBox = new TGListBox ( reacFrame, 90 );
    reacListBox->SetName ( "Reactions ListBox" );
    reacListBox->Resize ( 375, 150 );
    reacListBox->SetMultipleSelections ( kTRUE );

    reacFrame->AddFrame ( reacListLabel );
    reacFrame->AddFrame ( reacListBox );

    // ------ Creating Axis Choice Buttons ------ //

    TGCompositeFrame* axisCBFrame = new TGCompositeFrame ( reacFrame, 2000, 2000 );
    axisCBFrame->SetName ( "Axis Check Buttons Frame" );
    axisCBFrame->SetLayoutManager ( new TGRowLayout ( axisCBFrame, 60 ) );

    TGButtonGroup* xAxisBG = new TGButtonGroup ( axisCBFrame, "X Axis", kVerticalFrame );
    xAxisBG->SetName ( "X Axis BG" );
    TGRadioButton* ejecLabAngleCBX = new TGRadioButton ( xAxisBG, "Ejec. Lab Angle" );
    ejecLabAngleCBX->SetName ( "Ejec. Lab Angle CB X" );
    ejecLabAngleCBX->SetState ( kButtonDown );
    TGRadioButton* ejecLabEnergyCBX = new TGRadioButton ( xAxisBG, "Ejec. Lab Energy" );
    ejecLabEnergyCBX->SetName ( "Ejec. Lab Energy CB X" );
    TGRadioButton* ejecCMAngleCBX = new TGRadioButton ( xAxisBG, "Ejec. C.M. Angle" );
    ejecCMAngleCBX->SetName ( "Ejec. C.M. Angle CB X" );
    TGRadioButton* recLabAngleCBX = new TGRadioButton ( xAxisBG, "Recoil Lab Angle" );
    recLabAngleCBX->SetName ( "Recoil Lab Angle CB X" );
    TGRadioButton* recLabEnergyCBX = new TGRadioButton ( xAxisBG, "Recoil Lab Energy" );
    recLabEnergyCBX->SetName ( "Recoil Lab Energy CB X" );
    TGRadioButton* recCMAngleCBX = new TGRadioButton ( xAxisBG, "Recoil C.M. Angle" );
    recCMAngleCBX->SetName ( "Recoil C.M. Angle CB X" );
    xAxisBG->Show();

    TGButtonGroup* yAxisBG = new TGButtonGroup ( axisCBFrame, "Y Axis", kVerticalFrame );
    yAxisBG->SetName ( "Y Axis BG" );
    TGRadioButton* ejecLabAngleCBY = new TGRadioButton ( yAxisBG, "Ejec. Lab Angle" );
    ejecLabAngleCBY->SetName ( "Ejec. Lab Angle CB X" );
    TGRadioButton* ejecLabEnergyCBY = new TGRadioButton ( yAxisBG, "Ejec. Lab Energy" );
    ejecLabEnergyCBY->SetName ( "Ejec. Lab Energy CB X" );
    ejecLabEnergyCBY->SetState ( kButtonDown );
    TGRadioButton* ejecCMAngleCBY = new TGRadioButton ( yAxisBG, "Ejec. C.M. Angle" );
    ejecCMAngleCBY->SetName ( "Ejec. C.M. Angle CB X" );
    TGRadioButton* recLabAngleCBY = new TGRadioButton ( yAxisBG, "Recoil Lab Angle" );
    recLabAngleCBY->SetName ( "Recoil Lab Angle CB X" );
    TGRadioButton* recLabEnergyCBY = new TGRadioButton ( yAxisBG, "Recoil Lab Energy" );
    recLabEnergyCBY->SetName ( "Recoil Lab Energy CB X" );
    TGRadioButton* recCMAngleCBY = new TGRadioButton ( yAxisBG, "Recoil C.M. Angle" );
    recCMAngleCBY->SetName ( "Recoil C.M. Angle CB X" );
    yAxisBG->Show();

    axisCBFrame->AddFrame ( xAxisBG );
    axisCBFrame->AddFrame ( yAxisBG );

    reacFrame->AddFrame ( axisCBFrame );

    // ------ Creating Axis Range IF and Plot Button ------ //

    TGCompositeFrame* plotOptionsFrame = new TGCompositeFrame ( reacFrame, 2000, 2000 );
    plotOptionsFrame->SetName ( "Plot Options Frame" );
    plotOptionsFrame->SetLayoutManager ( new TGRowLayout ( plotOptionsFrame, 25 ) );

    TGCompositeFrame* axisLabelsFrame = new TGCompositeFrame ( plotOptionsFrame, 2000, 2000 );
    axisLabelsFrame->SetName ( "Axis Labels Frame" );
    axisLabelsFrame->SetLayoutManager ( new TGColumnLayout ( axisLabelsFrame, 20 ) );

    TGLabel* xMinLabel = new TGLabel ( axisLabelsFrame, "X Min:" );
    TGLabel* xMaxLabel = new TGLabel ( axisLabelsFrame, "X Max:" );
    TGLabel* xStepLabel = new TGLabel ( axisLabelsFrame, "Step Width:" );

    axisLabelsFrame->AddFrame ( xMinLabel );
    axisLabelsFrame->AddFrame ( xMaxLabel );
    axisLabelsFrame->AddFrame ( xStepLabel );

    plotOptionsFrame->AddFrame ( axisLabelsFrame );

    TGCompositeFrame* axisIFFrame = new TGCompositeFrame ( plotOptionsFrame, 2000, 2000 );
    axisIFFrame->SetName ( "Axis IF Frame" );
    axisIFFrame->SetLayoutManager ( new TGColumnLayout ( axisIFFrame, 20 ) );

    TGNumberEntryField* xMinIF = new TGNumberEntryField ( axisIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    xMinIF->SetName ( "X Min IF" );
    xMinIF->SetNumber ( 0.0 );
    TGNumberEntryField* xMaxIF = new TGNumberEntryField ( axisIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    xMaxIF->SetName ( "X Max IF" );
    xMaxIF->SetNumber ( 180.0 );
    TGNumberEntryField* xStepIF = new TGNumberEntryField ( axisIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    xStepIF->SetName ( "Step Width IF" );
    xStepIF->SetNumber ( 1.0 );

    axisIFFrame->AddFrame ( xMinIF );
    axisIFFrame->AddFrame ( xMaxIF );
    axisIFFrame->AddFrame ( xStepIF );

    plotOptionsFrame->AddFrame ( axisIFFrame );

    TGCompositeFrame* plotButtonFrame = new TGCompositeFrame ( plotOptionsFrame, 2000, 2000 );
    plotButtonFrame->SetName ( "Plot Button Frame" );
    plotButtonFrame->SetLayoutManager ( new TGColumnLayout ( plotButtonFrame, 20 ) );

    TGLabel* emptySpace1 = new TGLabel ( plotButtonFrame, "" );
    TGTextButton* plotGraphs = new TGTextButton ( plotButtonFrame, "Plot Graphs", "RootKinCalc::OnClickPlotGraphs()" );
    plotGraphs->SetFont ( "-*-helvetica-medium-r-*-*-16-*-*-*-*-*-iso8859-1" );
    plotGraphs->Resize ( plotGraphs->GetDefaultSize() );

    plotButtonFrame->AddFrame ( emptySpace1 );
    plotButtonFrame->AddFrame ( plotGraphs );

    plotOptionsFrame->AddFrame ( plotButtonFrame );

    reacFrame->AddFrame ( plotOptionsFrame );

    mainIFFrame->AddFrame ( reacFrame );

    // ------ Creating Reaction Labels Frame ------ //

    TGCompositeFrame* reacLabelsFrame = new TGCompositeFrame ( mainIFFrame, 2000, 2000 );
    reacLabelsFrame->SetName ( "Reaction Labels Frame" );
    reacLabelsFrame->SetLayoutManager ( new TGColumnLayout ( reacLabelsFrame, 26 ) );

    TGLabel* emptyCell1 = new TGLabel ( reacLabelsFrame, "" );
    TGLabel* beamLabel = new TGLabel ( reacLabelsFrame, "Beam:" );
    TGLabel* targetLabel = new TGLabel ( reacLabelsFrame, "Target:" );
    TGLabel* ejecLabel = new TGLabel ( reacLabelsFrame, "Ejectile:" );
    TGLabel* recoilLabel = new TGLabel ( reacLabelsFrame, "Recoil:" );

    reacLabelsFrame->AddFrame ( emptyCell1 );
    reacLabelsFrame->AddFrame ( beamLabel );
    reacLabelsFrame->AddFrame ( targetLabel );
    reacLabelsFrame->AddFrame ( ejecLabel );
    reacLabelsFrame->AddFrame ( recoilLabel );

    mainIFFrame->AddFrame ( reacLabelsFrame );

    // ------ Creating Elements IF Labels Frame ------ //

    TGCompositeFrame* elIFFrame = new TGCompositeFrame ( mainIFFrame, 2000, 2000 );
    elIFFrame->SetName ( "Elements IF Frame" );
    elIFFrame->SetLayoutManager ( new TGColumnLayout ( elIFFrame, 20 ) );

    TGLabel* elLabel = new TGLabel ( elIFFrame, "               Element" );
    beamElLabel = new TGTextEntry ( elIFFrame );
    targetElLabel = new TGTextEntry ( elIFFrame );
    ejecElLabel = new TGTextEntry ( elIFFrame );
    recoilElLabel = new TGTextEntry ( elIFFrame );
    recoilElLabel->SetState ( kFALSE );

    elIFFrame->AddFrame ( elLabel );
    elIFFrame->AddFrame ( beamElLabel );
    elIFFrame->AddFrame ( targetElLabel );
    elIFFrame->AddFrame ( ejecElLabel );
    elIFFrame->AddFrame ( recoilElLabel );

    mainIFFrame->AddFrame ( elIFFrame );

    // ------ Creating Kinetic Energy IF Labels Frame ------ //

    TGCompositeFrame* keIFFrame = new TGCompositeFrame ( mainIFFrame, 2000, 2000 );
    keIFFrame->SetName ( "Kinetic Energy IF Frame" );
    keIFFrame->SetLayoutManager ( new TGColumnLayout ( keIFFrame, 20 ) );

    TGLabel* keLabel = new TGLabel ( keIFFrame, "           Kinetic Energy" );
    beamKeLabel = new TGNumberEntryField ( keIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    beamKeLabel->SetNumber ( 0 );
//     targetKeLabel = new TGNumberEntryField ( keIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
//     ejecKeLabel = new TGNumberEntryField ( keIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
//     recoilKeLabel = new TGNumberEntryField ( keIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
//     recoilElLabel->SetState ( kFALSE );

    keIFFrame->AddFrame ( keLabel );
    keIFFrame->AddFrame ( beamKeLabel );
//     keIFFrame->AddFrame ( targetKeLabel );
//     keIFFrame->AddFrame ( ejecKeLabel );
//     keIFFrame->AddFrame ( recoilKeLabel );

    mainIFFrame->AddFrame ( keIFFrame );

    // ------ Creating Excitation Energy IF Labels Frame ------ //

    TGCompositeFrame* exIFFrame = new TGCompositeFrame ( mainIFFrame, 2000, 2000 );
    exIFFrame->SetName ( "Excitation Energy IF Frame" );
    exIFFrame->SetLayoutManager ( new TGColumnLayout ( exIFFrame, 20 ) );

    TGLabel* exLabel = new TGLabel ( exIFFrame, "      Excitation Energy" );
    beamExLabel = new TGNumberEntryField ( exIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    beamExLabel->SetNumber ( 0 );
    targetExLabel = new TGNumberEntryField ( exIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    targetExLabel->SetNumber ( 0 );
    ejecExLabel = new TGNumberEntryField ( exIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    ejecExLabel->SetNumber ( 0 );
    recoilExLabel = new TGNumberEntryField ( exIFFrame, -1, 0, TGNumberFormat::kNESReal, TGNumberFormat::kNEAPositive );
    recoilExLabel->SetNumber ( 0 );
    recoilElLabel->SetState ( kFALSE );

    exIFFrame->AddFrame ( exLabel );
    exIFFrame->AddFrame ( beamExLabel );
    exIFFrame->AddFrame ( targetExLabel );
    exIFFrame->AddFrame ( ejecExLabel );
    exIFFrame->AddFrame ( recoilExLabel );

    mainIFFrame->AddFrame ( exIFFrame );

    controlFrame->AddFrame ( mainIFFrame, new TGLayoutHints ( kLHintsLeft, 20, 20, 20, 10 ) );

    // ------ Creating Bottom Buttons Frame ------ //

    TGCompositeFrame* buttonsFrame = new TGCompositeFrame ( controlFrame, 2000, 2000 );
    buttonsFrame->SetName ( "Excitation Energy IF Frame" );
    buttonsFrame->SetLayoutManager ( new TGRowLayout ( buttonsFrame, 150 ) );

    // ------ Adding the actions buttons ------ //

    TGTextButton* getReacKin = new TGTextButton ( buttonsFrame, "Get Reaction Kinematic", "RootKinCalc::OnClickCalcKin()" );
    getReacKin->SetFont ( "-*-helvetica-medium-r-*-*-16-*-*-*-*-*-iso8859-1" );
    getReacKin->Resize ( getReacKin->GetDefaultSize() );

    buttonsFrame->AddFrame ( getReacKin );

    controlFrame->AddFrame ( buttonsFrame, new TGLayoutHints ( kLHintsCenterX, 0, 0, 10, 10 ) );

    // ------ Wraping everything in the main frame ------ //

//     controlFrame->ChangeSubframesBackground ( 0x4d004d );

    controlFrame->MapSubwindows();
    controlFrame->Resize ( controlFrame->GetDefaultSize() );
//     vertFrame->Resize ( vertFrame->GetDefaultSize() );
//     firstFrame->Resize ( firstFrame->GetDefaultSize() );
    controlFrame->MapWindow();

    theApp->Run();
}

