####################################################################################################
#MCInfo V6
####################################################################################################
#cross-section: the cross-section of the MC process in pb-1, 
#twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat8TeV
####################################################################################################
#Number of processed events: Number of events processed by CRAB. Not identical to number of produced events if not all grid jobs succeed!
####################################################################################################
#Number of produced events: Number of total events in the parent sample, i.e. 
#https://cmsweb.cern.ch/das/request?view=list&limit=10&instance=cms_dbs_prod_global&input=dataset%3D%2FElectronHad%2FRun2011A-08Nov2011-v1%2FAOD
####################################################################################################
#Number of selected events: Number of events passing the pre-selection at the nTuple process
####################################################################################################
#Naming of the samples:
#Please use the same naming as in (names array)
#https://svnweb.cern.ch/trac/bat/browser/trunk/AnalysisTools/interface/DataTypes.h
####################################################################################################

datasetInfo = {}
#if using the designated subset:
datasetInfo['TTGamma'] = {"cross-section": 1.8, "NumberOfProcessedEvents":1074860}
datasetInfo['TTJet'] = {"cross-section": 245.8, "NumberOfProcessedEvents":6923652}
datasetInfo['WJetsToLNu'] = {"cross-section": 36257.2, "NumberOfProcessedEvents":57709905}

datasetInfo['T_s-channel'] = {"cross-section": 3.89394, "NumberOfProcessedEvents":259911}
datasetInfo['T_t-channel'] = {"cross-section": 55.531, "NumberOfProcessedEvents":3757707}
datasetInfo['T_tW-channel'] = {"cross-section": 11.1773, "NumberOfProcessedEvents":493460}

datasetInfo['Tbar_s-channel'] = {"cross-section": 1.75776, "NumberOfProcessedEvents":139948}
datasetInfo['Tbar_t-channel'] = {"cross-section": 30.0042, "NumberOfProcessedEvents":1934817}
datasetInfo['Tbar_tW-channel'] = {"cross-section": 11.1773, "NumberOfProcessedEvents":497658}

#systematic samples
datasetInfo['TTJets-matchingdown'] = {"cross-section": 130., "NumberOfProcessedEvents":5458456}
datasetInfo['TTJets-matchingup'] = {"cross-section": 138., "NumberOfProcessedEvents":5412642}
datasetInfo['TTJets-scaledown'] = {"cross-section": 228.0, "NumberOfProcessedEvents":5384596}
datasetInfo['TTJets-scaleup'] = {"cross-section": 97.7, "NumberOfProcessedEvents":5007277}


#di lepton stuff
datasetInfo['DoubleMu'] = {"cross-section": 0, "NumberOfProcessedEvents":0}
datasetInfo['DoubleElectron'] = {"cross-section": 0, "NumberOfProcessedEvents":0}
datasetInfo['MuEG'] = {"cross-section": 0, "NumberOfProcessedEvents":0}

datasetInfo['WW'] = {"cross-section": 57.1097, "NumberOfProcessedEvents":10000431}
datasetInfo['WZ'] = {"cross-section": 32.3161, "NumberOfProcessedEvents":10000283}
datasetInfo['ZZ'] = {"cross-section": 8.25561, "NumberOfProcessedEvents":9799908}

#Ttbar + Z/W from http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2011_288_v14.pdf
datasetInfo['TTbarZIncl'] = {"cross-section": 0.14, "NumberOfProcessedEvents":196277}
datasetInfo['TTbarInclWIncl'] = {"cross-section": 0.16, "NumberOfProcessedEvents":349038}

#QCD
datasetInfo['QCD_Pt_20_MuEnrichedPt_15'] = {"cross-section": 3.64e8 * 3.7e-4, "NumberOfProcessedEvents":21484602}
datasetInfo['QCD_Pt_20_30_BCtoE'] = {"cross-section": 2.886e8 * 5.8e-4, "NumberOfProcessedEvents":1740229}
datasetInfo['QCD_Pt_30_80_BCtoE'] = {"cross-section": 7.424e7 * 0.00225, "NumberOfProcessedEvents":2048152}
datasetInfo['QCD_Pt_80_170_BCtoE'] = {"cross-section": 1191000.0 * 0.0109, "NumberOfProcessedEvents":1945525}
datasetInfo['QCD_Pt_20_30_EMEnriched'] = {"cross-section": 2.886e8 * 0.0101, "NumberOfProcessedEvents":35040695}
datasetInfo['QCD_Pt_30_80_EMEnriched'] = {"cross-section": 7.433e7 * 0.0621, "NumberOfProcessedEvents":33088888}
datasetInfo['QCD_Pt_80_170_EMEnriched'] = {"cross-section": 1191000.0 * 0.1539, "NumberOfProcessedEvents":34542763}


#extra ttbar samples
datasetInfo['TTJets_SemiLept'] = {"cross-section": 245.8, "NumberOfProcessedEvents":25424818}
datasetInfo['TTJets_FullLept'] = {"cross-section": 245.8, "NumberOfProcessedEvents":12111439}
datasetInfo['TTJets_Hadronic'] = {"cross-section": 245.8, "NumberOfProcessedEvents":27609920}
#extra DY samples
datasetInfo['DYJetsToLL_M-10To50'] = {"cross-section": 11050.0, "NumberOfProcessedEvents":37835275}
datasetInfo['DYJetsToLL_M-50'] = {"cross-section": 2950.0, "NumberOfProcessedEvents":30459503}

