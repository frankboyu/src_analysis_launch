/**************************************************************************                                                             
* HallD software                                                          * 
* Copyright(C) 2022       GlueX and Prim_-D Collaborations               * 
*                                                                         *                                                                
* Author: The GlueX and Prim_-D Collaborations                           *                                                                
* Contributors: Igal Jaegle                                               *                                                               
*                                                                         *
*                                                                         *   
* This software is provided "as is" without any warranty.                 *
**************************************************************************/

#ifndef _JEventProcessor_eta_ana_
#define _JEventProcessor_eta_ana_

#include <JANA/JEventProcessor.h>
#include <JANA/JApplication.h>

#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

#include <PID/DBeamPhoton.h>
#include <PID/DEventRFBunch.h>
#include <HDDM/DEventHitStatistics.h>
#include <FDC/DFDCPseudo.h>

#include <CCAL/DCCALShower.h>
#include <FCAL/DFCALShower.h>
#include <BCAL/DBCALShower.h>
#include <TOF/DTOFPoint.h>
#include "PID/DVertex.h"
#include <PID/DNeutralParticle.h>
#include <PID/DParticleID.h>
#include <CCAL/DCCALGeometry.h>
#include <FCAL/DFCALGeometry.h>
#include <FCAL/DFCALCluster.h>
#include <ECAL/DECALHit.h>
#include <FCAL/DFCALHit.h>
#include <BCAL/DBCALHit.h>
#include <FCAL/DFCALDigiHit.h>
#include <TRIGGER/DL1Trigger.h>
#include <TRIGGER/DL1MCTrigger.h>
#include <START_COUNTER/DSCHit.h>
#include "TRACKING/DMCThrown.h"
#include <HDGEOMETRY/DGeometry.h>
#include <PID/DChargedTrack.h>
#include "TRACKING/DTrackTimeBased.h"
//#include "HistogramTools.h"
#include "PID/DMCReaction.h"
#include <PID/DDetectorMatches.h>

#include "ANALYSIS/DTreeInterface.h"

#include <KINFITTER/DKinFitter.h>
#include <ANALYSIS/DKinFitUtils_GlueX.h>

#include "units.h"
#include "DLorentzVector.h"
#include "DVector3.h"
#include "TRandom3.h"

#include "Combination.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>

//using namespace jana;
using namespace std;



//class JEventProcessor_eta_ana:public jana::JEventProcessor{
class JEventProcessor_eta_ana:public JEventProcessor{
	public:
                JEventProcessor_eta_ana() {};
                ~JEventProcessor_eta_ana() {};
		const char* className(void){return "JEventProcessor_eta_ana";}

	private:
                void Init() override;
		void BeginRun(const std::shared_ptr<const JEvent>& event) override;
		void Process(const std::shared_ptr<const JEvent>& event) override;
		void EndRun() override;
		void Finish() override;
		
		//TREE
                DTreeInterface* dTreeInterface_gd_to_KY;
                DTreeInterface* dTreeInterface_gd_to_ee;
                DTreeInterface* dTreeInterface_gd_to_pn;
                DTreeInterface* dTreeInterface_pi0_to_gg;
                DTreeInterface* dTreeInterface_eta_to_gg;
                DTreeInterface* dTreeInterface_eta_to_gggg;
                DTreeInterface* dTreeInterface_eta_to_pi0pi0pi0;
                DTreeInterface* dTreeInterface_eta_to_pi0pippim;
                DTreeInterface* dTreeInterface_etap_to_etapi0pi0;
                DTreeInterface* dTreeInterface_etap_to_etapippim;
                DTreeInterface* dTreeInterfaceSimu_gd_to_ee;
                DTreeInterface* dTreeInterfaceSimu_gd_to_pn;
                DTreeInterface* dTreeInterfaceSimu_gd_to_KY;
                DTreeInterface* dTreeInterfaceSimu_pi0_to_gg;
                DTreeInterface* dTreeInterfaceSimu_eta_to_gg;
                DTreeInterface* dTreeInterfaceSimu_eta_to_gggg;
                DTreeInterface* dTreeInterfaceSimu_eta_to_pi0pi0pi0;
                DTreeInterface* dTreeInterfaceSimu_eta_to_pi0pippim;
                DTreeInterface* dTreeInterfaceSimu_etap_to_etapi0pi0;
                DTreeInterface* dTreeInterfaceSimu_etap_to_etapippim;
		
                //thread_local: Each thread has its own object: no lock needed
                //important: manages it's own data internally: don't want to call new/delete every event!

                static thread_local DTreeFillData dTreeFillData;
                static thread_local DTreeFillData dTreeFillSimu;
  
		int fcalLayer(int row, int col);
		
		int check_SC_match(double phi, double rfTime, vector< const DSCHit* > locSCHits, double &dphi_min);
		int check_TOF_match(DVector3 fcalpos, double rfTime, DVector3 vertex, vector<const DTOFPoint*> tof_points, double &dx_min, double &dy_min);
		vector<vector<DVector3> >sc_pos;
		vector<vector<DVector3> >sc_norm;
                float GetAccScalingFactor(float);
                void FillParticleVectors(vector<const DChargedTrack *>&tracks,
					     Particle_t particle_m,
					     Particle_t particle_p,
					     vector<const DTrackTimeBased *>&pims,
					     vector<const DTrackTimeBased *>&pips,
					     vector<int> &m_index,
					     vector<int> &p_index);
  
		double coshel(TLorentzVector, TLorentzVector, TLorentzVector);

                void Combined3g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Pi0,
				Double_t &bestChi2Eta,
				vector<int>&IndexPi0List,
				vector<int>&IndexEtaList);
  
		void Combined3g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2,
				vector<int>&IndexList);
  
               void Combined6g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);
		
		void combined6g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);

                void Combined7g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);
		
		void combined7g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);

		void Combined4g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Pi0Pi0,
				Double_t &bestChi2Pi0Eta,
				Double_t &bestChi2EtaEta,
				Double_t &bestChi2Pi0Etapr,
				Double_t &bestChi2EtaEtapr,
				Double_t &bestChi2EtaprEtapr,
				Double_t &bestChi2GGPi0,
				vector<int>&IndexPi0Pi0List,
				vector<int>&IndexPi0EtaList,
				vector<int>&IndexEtaEtaList,
				vector<int>&IndexPi0EtaprList,
				vector<int>&IndexEtaEtaprList,
				vector<int>&IndexEtaprEtaprList,
				vector<int>&IndexGGPi0List);

		void combined4g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Pi0Pi0,
				Double_t &bestChi2Pi0Eta,
				Double_t &bestChi2EtaEta,
				Double_t &bestChi2Pi0Etapr,
				Double_t &bestChi2EtaEtapr,
				Double_t &bestChi2EtaprEtapr,
				Double_t &bestChi2GGPi0,
				vector<int>&IndexPi0Pi0List,
				vector<int>&IndexPi0EtaList,
				vector<int>&IndexEtaEtaList,
				vector<int>&IndexPi0EtaprList,
				vector<int>&IndexEtaEtaprList,
				vector<int>&IndexEtaprEtaprList,
				vector<int>&IndexGGPi0List);

		void Combined5g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Pi0Pi0,
				Double_t &bestChi2Pi0Eta,
				Double_t &bestChi2EtaEta,
				Double_t &bestChi2Pi0Etapr,
				Double_t &bestChi2EtaEtapr,
				Double_t &bestChi2EtaprEtapr,
				Double_t &bestChi2GGPi0,
				vector<int>&IndexPi0Pi0List,
				vector<int>&IndexPi0EtaList,
				vector<int>&IndexEtaEtaList,
				vector<int>&IndexPi0EtaprList,
				vector<int>&IndexEtaEtaprList,
				vector<int>&IndexEtaprEtaprList,
				vector<int>&IndexGGPi0List);

		void combined5g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Pi0Pi0,
				Double_t &bestChi2Pi0Eta,
				Double_t &bestChi2EtaEta,
				Double_t &bestChi2Pi0Etapr,
				Double_t &bestChi2EtaEtapr,
				Double_t &bestChi2EtaprEtapr,
				Double_t &bestChi2GGPi0,
				vector<int>&IndexPi0Pi0List,
				vector<int>&IndexPi0EtaList,
				vector<int>&IndexEtaEtaList,
				vector<int>&IndexPi0EtaprList,
				vector<int>&IndexEtaEtaprList,
				vector<int>&IndexEtaprEtaprList,
				vector<int>&IndexGGPi0List);

  

		//Drew's fit
		double getEnergyRes(double e );
                double energy_after_recoil(double eb, double theta, double m0, double mp);
		//
		
                Combination  *combi3;       
		Combination  *combi4;       
                Combination  *combi5;       
                Combination  *combi6;       
		Combination  *combi7;       
                Particle_t TargetA;
		Particle_t TargetN;

                vector <Particle_t> t_trk_minus;
                vector <Particle_t> t_trk_plus;
                vector <TString> s_trk;

  bool m_gd_to_KY;
  bool m_gd_to_ee;
  bool m_gd_to_pn;
  bool m_pi0_to_gg;
  bool m_eta_to_gg;
  bool m_eta_to_gggg;
  bool m_eta_to_pi0pi0pi0;
  bool m_eta_to_pi0pippim;
  bool m_etap_to_etapi0pi0;
  bool m_etap_to_etapippim;
  
		double TargetMass;
		double m_beamX, m_beamY, m_beamZ;
		double m_fcalX, m_fcalY, m_fcalZ;
		double m_ccalX, m_ccalY, m_ccalZ;
                double m_ecalX, m_ecalY, m_ecalZ;
		int m_rnb;
		const double m_pi0 =  0.1349770;
		const double m_eta =  0.547862;
		const double massBe9 = 8.39479;
		const double massHe4 = 3.727379238;
		
		const double me = 0.510998928e-3;
		const double mp = 0.93827208816;
		const double m_etap = 0.95778;  
		
		const double FCAL_RF_CUT       =  3.0;
		const double CCAL_RF_CUT       =  3.0;
		const double BCAL_RF_CUT       =  6.012;
		const double TOF_RF_CUT       =  6.5;
		const double BEAM_RF_CUT       =  2.004;
		
		const double MIN_FCAL_ENERGY   =  0.5;
		const double MIN_BEAM_ENERGY   =  8.0;
                float m_HodoscopeHiFactor    = 1.0;
		float m_HodoscopeHiFactorErr = 1.0;
		float m_HodoscopeLoFactor    = 1.0;
		float m_HodoscopeLoFactorErr = 1.0;
		float m_MicroscopeFactor     = 1.0;
		float m_MicroscopeFactorErr  = 1.0;
		float m_TAGMEnergyBoundHi    = 1.0;
		float m_TAGMEnergyBoundLo    = 1.0;		
		int m_MakeTree;
		double m_im_gg_CUT;
		double m_FCAL_RF_CUT;
		double m_CCAL_RF_CUT;
                double m_ECAL_RF_CUT;
		double m_BCAL_RF_CUT;
                //double m_BCAL_RF_CUT_min;
		double m_BCAL_RF_CUT_max;
                //double m_FCAL_RF_CUT_min;
                double m_FCAL_RF_CUT_max;
                //double m_ECAL_RF_CUT_min;
                double m_ECAL_RF_CUT_max;
		double m_TOF_RF_CUT;
		double m_BEAM_RF_CUT;
		double m_MIN_BCAL_ENERGY;
		double m_MIN_FCAL_ENERGY;
		double m_MIN_CCAL_ENERGY;
                double m_MIN_ECAL_ENERGY;
		double m_MIN_BEAM_ENERGY;
		int USE_LO;
		int USE_EVIO;
                int ctr_trk0, ctr_trk1;
                double m_MIN_DE, m_MAX_DE, m_MIN_RDE, m_MAX_RDE;
		double m_MIN_IM, m_MAX_IM, m_MIN_RIM, m_MAX_RIM;
		TF1 * fct_edc;

  TH1F * h_la[20];
  TH1F * h_ka[20];
  TH1F * h_trg_bit;
                TH1F * h_trg_bit_mc;
                TH1F * h_r, * h_z, * h_z_calc, * h_z_fit;
		TH1F * h_pattern[10];
		TH1F * h_im2g[50];
  		TH1F * h_cop2g[6];
                TH1F * h_im4g[50];
  		TH1F * h_cop4g[6];
                TH1F * h_im6g[50];
  		TH1F * h_cop6g[6];
                TH1F * h_im2g2p[50];
  		TH1F * h_cop2g2p[6];
                TH1F * h_im_sel[50];
                TH2F * h_delta_z[4];
                TH1F * h_sign_dis[10];
};

#endif // _JEventProcessor_eta_ana_

