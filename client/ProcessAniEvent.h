#pragma once

class CAniObj;

enum
{
	eEvent_AttackEffect,//공격 이벤트
	eEvent_ChangeState,//상태 변경 이벤트
	eEvent_Die//죽은 상태 이벤트
};

void OnAniEvent( CAniObj* pAniObj, const SAniEventData& sData );