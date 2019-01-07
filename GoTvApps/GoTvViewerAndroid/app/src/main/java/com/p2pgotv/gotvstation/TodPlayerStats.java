package com.p2pgotv.gotvstation;

class TodPlayerStats
{
	//=== vars ===//
	int						m_s32DareChallengeCnt = 0;
	int						m_s32DareAcceptedCnt = 0;
	int						m_s32DareRejectedCnt = 0;
	int						m_s32TruthChallengeCnt = 0;
	int						m_s32TruthAcceptedCnt = 0;
	int						m_s32TruthRejectedCnt = 0;

	static public final int eTodGameVarIdDareChallengeCnt = 0;
	static public final int eTodGameVarIdDareAcceptedCnt = 1;
	static public final int  eTodGameVarIdDareRejectedCnt = 2;
	static public final int eTodGameVarIdTruthChallengeCnt = 3;
	static public final int eTodGameVarIdTruthAcceptedCnt = 4;
	static public final int eTodGameVarIdTruthRejectedCnt = 5;
	static public final int eMaxTodGameStatId = 6;
	static public final int eMaxTodGameVarId = 7;


	//========================================================================
	TodPlayerStats()
	{
	}

	//========================================================================
	int getVar( int eVarId )
	{
		switch(eVarId)
		{
		case eTodGameVarIdDareChallengeCnt:
			return m_s32DareChallengeCnt;
		case eTodGameVarIdDareAcceptedCnt:
			return m_s32DareAcceptedCnt;
		case eTodGameVarIdDareRejectedCnt:
			return m_s32DareRejectedCnt;
		case eTodGameVarIdTruthChallengeCnt:
			return m_s32TruthChallengeCnt;
		case eTodGameVarIdTruthAcceptedCnt:
			return m_s32TruthAcceptedCnt;
		case eTodGameVarIdTruthRejectedCnt:
			return m_s32TruthRejectedCnt;
		default:
			return 0;
		}		
	}

	//========================================================================
	void setVar( int eVarId, int s32Value )
	{
		switch(eVarId)
		{
		case eTodGameVarIdDareChallengeCnt:
			m_s32DareChallengeCnt = s32Value;
			break;
		case eTodGameVarIdDareAcceptedCnt:
			m_s32DareAcceptedCnt = s32Value;
			break;
		case eTodGameVarIdDareRejectedCnt:
			m_s32DareRejectedCnt = s32Value;
			break;
		case eTodGameVarIdTruthChallengeCnt:
			m_s32TruthChallengeCnt = s32Value;
			break;
		case eTodGameVarIdTruthAcceptedCnt:
			m_s32TruthAcceptedCnt = s32Value;
			break;
		case eTodGameVarIdTruthRejectedCnt:
			m_s32TruthRejectedCnt = s32Value;
			break;
		}		
	}
};