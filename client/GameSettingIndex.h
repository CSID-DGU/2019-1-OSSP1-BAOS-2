#pragma once

namespace GameSettingIndex//게임에서 설정한 기준 index
{
	const float CreateSmallCreatureTime = 2.0f;//작은 크리쳐를 생성하는데 걸리는 시간
	const float CreateBigCreatureTime = 10.0f;//큰 크리쳐를 생성하는데 걸리는 시간

	const float UpdateDarkTime = 0.5f;//dark업데이트시 걸리는 시간 설정
	const float UpdateDarkResetTime = 3.0f;//dark 리셋시 걸리는 시간 설정
	
	const float SkillCoolTime1 = 1.0f;//첫번째 스킬 쿨타임, 이 시간동안은 스킬 재사용 불가
	const float SkillCoolTime2 = 1.0f;//두번째 스킬 쿨타임, 이 시간동안은 스킬 재사용 불가
};