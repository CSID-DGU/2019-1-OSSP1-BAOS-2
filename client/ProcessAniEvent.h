#pragma once

class CAniObj;

enum
{
	eEvent_AttackEffect,//���� �̺�Ʈ
	eEvent_ChangeState,//���� ���� �̺�Ʈ
	eEvent_Die//���� ���� �̺�Ʈ
};

void OnAniEvent( CAniObj* pAniObj, const SAniEventData& sData );