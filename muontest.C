#include <iostream>
#include "TClonesArray.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TSystem.h"

#include "/home/yeop/Delphes-3.4.2/classes/DelphesClasses.h" //-Edit path  Delphes_Directory_location/classes/DelphesClasses.h


int main() {

	using namespace std;
	


	TChain* inChain = new TChain("Delphes"); // Read Tree
	inChain->Add("/home/yeop/Delphes-3.4.2/muontest.root"); //Read File

	TClonesArray* mTCA = new TClonesArray("Muon");
	inChain->SetBranchAddress("Muon",&mTCA); // Read Branch ( or leaf )

	TFile *outFile = new TFile("muontest.root","recreate"); // output file format

	TH1F* h1_mPt = new TH1F("h1_mPT","h1_mPT",200,0,100); 
	TH1F* h1_mmM = new TH1F("h1_mmM","h1_mmM",200,0,200);


	int totalN = inChain->GetEntries();

	// --Event Loop start
	for(int eventLoop=0; eventLoop<totalN; eventLoop++){
	inChain->GetEntry(eventLoop); // Access Entry 

			// --Muon Loop start
			for(int eLoop=0; eLoop<mTCA->GetEntries(); eLoop++){
			Muon* mPtr = (Muon*)mTCA->At(eLoop);
		
			h1_mPt->Fill(mPtr->PT);
	      	} // Muon Loop end
		
	if(mTCA->GetEntries() != 2) continue;
	
		Muon* mPtr1 = (Muon*)mTCA->At(0);
		Muon* mPtr2 = (Muon*)mTCA->At(1);
		
	if(mPtr1->Charge * mPtr2->Charge > 0) continue;
		TLorentzVector mTVec1 = mPtr1->P4();
		TLorentzVector mTVec2 = mPtr2->P4();
		TLorentzVector mmTVec = mTVec1+mTVec2;
	
		h1_mmM->Fill(mmTVec.M());
	
	}// --Event Loop end
	
	// -- Write output file 
	outFile->Write();	


	// -- Draw image
	TCanvas* c1 = new TCanvas();
	h1_mPt->Draw();
	c1->Print("muonPT.png");
	TCanvas* c2 = new TCanvas();
	h1_mmM->Draw();
	c2->Print("Zmass.png");

	return 0;
}
