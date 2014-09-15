/*
 * EventCountAnalyser.h
 *
 *  Created on: 24 Mar 2011
 *      Author: kreczko
 */

#ifndef EVENTCOUNTANALYSER_H_
#define EVENTCOUNTANALYSER_H_

#include "BasicAnalyser.h"

//DiLepton
#include "../Selections/TopPairMuMuReferenceSelection.h"
#include "../Selections/TopPairEEReferenceSelection.h"
#include "../Selections/TopPairEMuReferenceSelection.h"
#include "../Selections/TopPairMuMuLooseReferenceSelection.h"
#include "../Selections/TopPairEELooseReferenceSelection.h"
#include "../Selections/TopPairEMuLooseReferenceSelection.h"

namespace BAT {

class EventCountAnalyser: public BAT::BasicAnalyser {
public:
	EventCountAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "EventCount");
	virtual ~EventCountAnalyser();
	virtual void analyse(const EventPtr);
	virtual void createHistograms();
	void setHistogramLabels();

	//Normal selection
	void topMuMuReferenceSelection(const EventPtr event);
	void topMuMuReferenceSelectionUnweighted(const EventPtr event);
	void topEEReferenceSelection(const EventPtr event);
	void topEEReferenceSelectionUnweighted(const EventPtr event);
	void topEMuReferenceSelection(const EventPtr event);
	void topEMuReferenceSelectionUnweighted(const EventPtr event);

	//Loose selection
        void topMuMuLooseReferenceSelection(const EventPtr event);
        void topMuMuLooseReferenceSelectionUnweighted(const EventPtr event);
        void topEELooseReferenceSelection(const EventPtr event);
        void topEELooseReferenceSelectionUnweighted(const EventPtr event);
        void topEMuLooseReferenceSelection(const EventPtr event);
        void topEMuLooseReferenceSelectionUnweighted(const EventPtr event);
	
	void individualCuts(const EventPtr event);

private:
	//dilepton normal
	SelectionPointer topMuMuRefSelection_;
	SelectionPointer topEERefSelection_;
	SelectionPointer topEMuRefSelection_;

	SelectionPointer topMuMuLooseRefSelection_;
        SelectionPointer topEELooseRefSelection_;
        SelectionPointer topEMuLooseRefSelection_;
};

} /* namespace BAT */
#endif /* EVENTCOUNTANALYSER_H_ */

