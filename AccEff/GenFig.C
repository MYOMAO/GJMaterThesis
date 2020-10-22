#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <Riostream.h>

#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"

#include "TH1.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"

#include "TPaveStats.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"


//#include "outsideSource/lhcb.C"
#endif
using namespace std;


void GenFig(){

	gStyle->SetOptStat(0);

	const int NPtBin = 4;
	double Pt[NPtBin] = {8.5,12.5,17.5,35};
	double PtWidth[NPtBin] = {1.5,2.5,2.5,15};
	double PtEff[NPtBin] = {101.502,36.2655,10.9027,5.99082};
	double PtEffUpPercent[NPtBin] = {0.123,0.0438,0.0146,0.0168};
	double PtEffDownPercent[NPtBin] = {0.122,0.0405,0.0173,0.0164};

	double PtEffUp[NPtBin];
	double PtEffDown[NPtBin];

	for(int i = 0; i < NPtBin; i++){

		PtEffUp[i] = PtEff[i] * PtEffUpPercent[i];
		PtEffDown[i] = PtEff[i] * PtEffDownPercent[i];


		cout << "i = " << i  << "  PtEffUp = " << PtEffUp[i] << "  PtEffDown = " << PtEffDown[i] << endl;

	}


	const int NCentBin = 2;
	double Cent[NCentBin] = {15,60};
	double CentWidth[NCentBin] = {15,30};
	double CentEff[NCentBin] = {21.1439,11.9747};
	double CentEffUpPercent[NCentBin] = {0.0445,0.0561};
	double CentEffDownPercent[NCentBin] = {0.0458,0.0546};

	double CentEffUp[NCentBin];
	double CentEffDown[NCentBin];

	for(int i = 0; i < NCentBin; i++){

		CentEffUp[i] = CentEff[i] * CentEffUpPercent[i];
		CentEffDown[i] = CentEff[i] * CentEffDownPercent[i];

		cout << "i = " << i  << "  CentEffUp = " << CentEffUp[i] << "  CentEffDown = " << CentEffDown[i] << endl;

	}


	const int NIncBin = 1;
	double Inc[NIncBin] = {45};
	double IncWidth[NIncBin] = {45};
	double IncEff[NIncBin] = {21.1439};
	double IncEffUpPercent[NIncBin] = {0.0380};
	double IncEffDownPercent[NIncBin] = {0.0377};

	double IncEffUp[NIncBin];
	double IncEffDown[NIncBin];

	for(int i = 0; i < NIncBin; i++){

		IncEffUp[i] = IncEff[i] * IncEffUpPercent[i];
		IncEffDown[i] = IncEff[i] * IncEffDownPercent[i];

		cout << "i = " << i  << "  IncEffUp = " << IncEffUp[i] << "  IncEffDown = " << IncEffDown[i] << endl;

	}





	TGraphAsymmErrors *PtEffGraph    = new TGraphAsymmErrors(NPtBin,Pt,PtEff,PtWidth,PtWidth,PtEffUp,PtEffDown);
	TGraphAsymmErrors *CentEffGraph    = new TGraphAsymmErrors(NCentBin,Cent,CentEff,CentWidth,CentWidth,CentEffUp,CentEffDown);
	TGraphAsymmErrors *IncEffGraph    = new TGraphAsymmErrors(NIncBin,Inc,IncEff,IncWidth,IncWidth,IncEffUp,IncEffDown);


	PtEffGraph->SetMarkerStyle(20);
	PtEffGraph->SetMarkerSize(1.0);
	PtEffGraph->SetMarkerColor(kBlack);


	TH2D * EmptyHisPt = new TH2D("EmptyHisPt","",100,7,50,100,0,140);
	EmptyHisPt->GetXaxis()->SetTitle("B^{+} p_T (GeV/c)");
	EmptyHisPt->GetYaxis()->SetTitle("<1/(acc * eff)>");
	EmptyHisPt->GetXaxis()->CenterTitle();
	EmptyHisPt->GetYaxis()->CenterTitle();


	TH2D * EmptyHisCent = new TH2D("EmptyHisCent","",100,0,90,100,0,30);
	EmptyHisCent->GetXaxis()->SetTitle("Event Centrality (%)");
	EmptyHisCent->GetYaxis()->SetTitle("<1/(acc * eff)>");
	EmptyHisCent->GetXaxis()->CenterTitle();
	EmptyHisCent->GetYaxis()->CenterTitle();



	TH2D * EmptyHisInc = new TH2D("EmptyHisCent","",100,0,90,100,0,30);
	EmptyHisCent->GetXaxis()->SetTitle("Event Centrality (%)");
	EmptyHisCent->GetYaxis()->SetTitle("<1/(acc * eff)>");
	EmptyHisCent->GetXaxis()->CenterTitle();
	EmptyHisCent->GetYaxis()->CenterTitle();



	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();

	EmptyHisPt->Draw();
	PtEffGraph->Draw("ePSame");



	c->SaveAs("Fig/PtEff.pdf");

	EmptyHisCent->Draw();
	CentEffGraph->Draw("ePSame");


	c->SaveAs("Fig/CentEff.pdf");


	EmptyHisInc->Draw();
	IncEffGraph->Draw("ePSame");


	c->SaveAs("Fig/IncEff.pdf");


}
