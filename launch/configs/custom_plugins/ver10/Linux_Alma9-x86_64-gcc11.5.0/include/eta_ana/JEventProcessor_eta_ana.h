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
#include <FCAL/DFCALHit.h>
#include <FCAL/DFCALDigiHit.h>
#include <TRIGGER/DL1Trigger.h>
#include <START_COUNTER/DSCHit.h>
#include "TRACKING/DMCThrown.h"
#include <HDGEOMETRY/DGeometry.h>
#include <PID/DChargedTrack.h>
#include "TRACKING/DTrackTimeBased.h"
#include "HistogramTools.h"
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

using namespace jana;
using namespace std;



class JEventProcessor_eta_ana:public jana::JEventProcessor{
	public:
		JEventProcessor_eta_ana();
		~JEventProcessor_eta_ana();
		const char* className(void){return "JEventProcessor_eta_ana";}

	private:
		jerror_t init(void);
		jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber);
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);
		jerror_t erun(void);
		jerror_t fini(void);
		
		//TREE
                DTreeInterface* dTreeInterface;
                DTreeInterface* dTreeInterfaceSimu;
		
                //thread_local: Each thread has its own object: no lock needed
                //important: manages it's own data internally: don't want to call new/delete every event!

                static thread_local DTreeFillData dTreeFillData;
                static thread_local DTreeFillData dTreeFillSimu;
  
		int fcalLayer(int row, int col);
		
		int check_SC_match(double phi, double rfTime, vector< const DSCHit* > locSCHits, double &dphi_min);
		int check_TOF_match(DVector3 fcalpos, double rfTime, DVector3 vertex, vector<const DTOFPoint*> tof_points, double &dx_min, double &dy_min);
		vector<vector<DVector3> >sc_pos;
		vector<vector<DVector3> >sc_norm;

		jerror_t FillParticleVectors(vector<const DChargedTrack *>&tracks,
					     Particle_t particle_m,
					     Particle_t particle_p,
					     vector<const DTrackTimeBased *>&pims,
					     vector<const DTrackTimeBased *>&pips,
					     vector<int> &m_index,
					     vector<int> &p_index);
		
		double coshel(TLorentzVector, TLorentzVector, TLorentzVector);

                void Combined3g(vector<const DNeutralParticleHypothesis *>&EMList,
				Double_t &bestChi2Pi0,
				Double_t &bestChi2Eta,
				vector<int>&IndexPi0List,
				vector<int>&IndexEtaList);
  
		void Combined3g(vector<const DNeutralParticleHypothesis *>&EMList,
				Double_t &bestChi2,
				vector<int>&IndexList);
  
               void Combined6g(vector<const DNeutralParticleHypothesis *>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);
		
		void combined6g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);

  		void Combined7g(vector<const DNeutralParticleHypothesis *>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);
		
		void combined7g(vector<DLorentzVector>&EMList,
				Double_t &bestChi2Eta,
				Double_t &bestChi2EtaPrim,
				vector<int>&Index6gList,
				vector<int>&Indexprim6gList);

		void Combined4g(vector<const DNeutralParticleHypothesis *>&EMList,
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

		void Combined5g(vector<const DNeutralParticleHypothesis *>&EMList,
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

		double TargetMass;
		double m_beamX, m_beamY, m_beamZ;
		double m_fcalX, m_fcalY, m_fcalZ;
		double m_ccalX, m_ccalY, m_ccalZ;
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
		
		int m_MakeTree;
		double m_im_gg_CUT;
		double m_FCAL_RF_CUT;
		double m_CCAL_RF_CUT;
		double m_BCAL_RF_CUT;
		double m_BCAL_RF_CUT_min;
		double m_BCAL_RF_CUT_max;
                double m_FCAL_RF_CUT_min;
		double m_FCAL_RF_CUT_max;
		double m_TOF_RF_CUT;
		double m_BEAM_RF_CUT;
		double m_MIN_BCAL_ENERGY;
		double m_MIN_FCAL_ENERGY;
		double m_MIN_CCAL_ENERGY;
		double m_MIN_BEAM_ENERGY;
		int USE_LO;
		int USE_EVIO;

                double m_MIN_DE, m_MAX_DE, m_MIN_RDE, m_MAX_RDE;
		double m_MIN_IM, m_MAX_IM, m_MIN_RIM, m_MAX_RIM;
		TF1 * fct_edc;
				
		TH1F * h_trg_bit;
		TH1F * h_r, * h_z;
		TH1F * h_pattern[10];
		TH1F * h_im[20];
		TH2F * h_nl[25];
		TH2F * h_wnl[3][25];
		TH2F * h_snl[3][25];
		TH1F * h_cs;
		TH1F * h_wcs[3];
		TH1F * h_cop[6];
};

#endif // _JEventProcessor_eta_ana_

