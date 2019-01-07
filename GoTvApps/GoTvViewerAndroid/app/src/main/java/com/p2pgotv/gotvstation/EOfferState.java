package com.p2pgotv.gotvstation;

public enum EOfferState
{
	eOfferStateUnknown,
	eOfferStateRxedOffer,
	eOfferStateOfferCanceled,
	eOfferStateSentAccept,
	eOfferStateSentRejected,

	eOfferStateWaitingReply,
	eOfferStateReplyBusy,
	eOfferStateReplyAccept,
	eOfferStateReplyRejected,
	eOfferStateReplyCanceled,
	eOfferStateReplyEndSession,
	
	eOfferStateInSession,
	eOfferStateUserOffline,
}
