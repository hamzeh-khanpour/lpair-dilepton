//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar  3 20:18:50 2024 by ROOT version 6.24/06
// from TTree h4444/A TTree containing information from the events produced from LPAIR
// found on file: events.root
//////////////////////////////////////////////////////////

#ifndef dimuon_h
#define dimuon_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "Math/GenVector/PxPyPzE4D.h"

class dimuon {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.  
   static constexpr Int_t kMaxmomentum = 1;

   // Declaration of leaf types
   Int_t           npart;
   Int_t           nremn_charged[2];
   Int_t           nremn_neutral[2];
   Int_t           role[9];   //[npart]
   Int_t           momentum_;
   Double_t        momentum_fCoordinates_fX[kMaxmomentum];   //[momentum_]
   Double_t        momentum_fCoordinates_fY[kMaxmomentum];   //[momentum_]
   Double_t        momentum_fCoordinates_fZ[kMaxmomentum];   //[momentum_]
   Double_t        momentum_fCoordinates_fT[kMaxmomentum];   //[momentum_]
   Double_t        pt[9];   //[npart]
   Double_t        eta[9];   //[npart]
   Double_t        phi[9];   //[npart]
   Double_t        rapidity[9];   //[npart]
   Double_t        E[9];   //[npart]
   Double_t        m[9];   //[npart]
   Double_t        charge[9];   //[npart]
   Int_t           pdg_id[9];   //[npart]
   Int_t           parent1[9];   //[npart]
   Int_t           parent2[9];   //[npart]
   Int_t           stable[9];   //[npart]
   Int_t           status[9];   //[npart]
   Float_t         generation_time;
   Float_t         total_time;

   // List of branches
   TBranch        *b_npart;   //!
   TBranch        *b_nremn_charged;   //!
   TBranch        *b_nremn_neutral;   //!
   TBranch        *b_role;   //!
   TBranch        *b_momentum_;   //!
   TBranch        *b_momentum_fCoordinates_fX;   //!
   TBranch        *b_momentum_fCoordinates_fY;   //!
   TBranch        *b_momentum_fCoordinates_fZ;   //!
   TBranch        *b_momentum_fCoordinates_fT;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_rapidity;   //!
   TBranch        *b_E;   //!
   TBranch        *b_m;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_pdg_id;   //!
   TBranch        *b_parent1;   //!
   TBranch        *b_parent2;   //!
   TBranch        *b_stable;   //!
   TBranch        *b_status;   //!
   TBranch        *b_generation_time;   //!
   TBranch        *b_total_time;   //!

   dimuon(TTree *tree=0);
   virtual ~dimuon();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef dimuon_cxx
dimuon::dimuon(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("events.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("events.root");
      }
      f->GetObject("h4444",tree);

   }
   Init(tree);
}

dimuon::~dimuon()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dimuon::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t dimuon::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void dimuon::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("npart", &npart, &b_npart);
   fChain->SetBranchAddress("nremn_charged", nremn_charged, &b_nremn_charged);
   fChain->SetBranchAddress("nremn_neutral", nremn_neutral, &b_nremn_neutral);
   fChain->SetBranchAddress("role", role, &b_role);
   fChain->SetBranchAddress("momentum", &momentum_, &b_momentum_);
   fChain->SetBranchAddress("momentum.fCoordinates.fX", &momentum_fCoordinates_fX, &b_momentum_fCoordinates_fX);
   fChain->SetBranchAddress("momentum.fCoordinates.fY", &momentum_fCoordinates_fY, &b_momentum_fCoordinates_fY);
   fChain->SetBranchAddress("momentum.fCoordinates.fZ", &momentum_fCoordinates_fZ, &b_momentum_fCoordinates_fZ);
   fChain->SetBranchAddress("momentum.fCoordinates.fT", &momentum_fCoordinates_fT, &b_momentum_fCoordinates_fT);
   fChain->SetBranchAddress("pt", pt, &b_pt);
   fChain->SetBranchAddress("eta", eta, &b_eta);
   fChain->SetBranchAddress("phi", phi, &b_phi);
   fChain->SetBranchAddress("rapidity", rapidity, &b_rapidity);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("m", m, &b_m);
   fChain->SetBranchAddress("charge", charge, &b_charge);
   fChain->SetBranchAddress("pdg_id", pdg_id, &b_pdg_id);
   fChain->SetBranchAddress("parent1", parent1, &b_parent1);
   fChain->SetBranchAddress("parent2", parent2, &b_parent2);
   fChain->SetBranchAddress("stable", stable, &b_stable);
   fChain->SetBranchAddress("status", status, &b_status);
   fChain->SetBranchAddress("generation_time", &generation_time, &b_generation_time);
   fChain->SetBranchAddress("total_time", &total_time, &b_total_time);
   Notify();
}

Bool_t dimuon::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dimuon::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dimuon::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef dimuon_cxx
