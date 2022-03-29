#pragma once
#include "../SubHeader.h"

// 콜리전 구조를 만들 것이고 나는 단순하게 렉트만 할 것이다.
class CollisionManager
{
//이너클래스

	class Collision
	{
	private:
		// 1. 너의 위치 (난 상대위치 같은거 안쓸거고 월드위치만 사용한다. (충돌에서는 상대위치를 쓰는 것은 혼란만 준다)
		// 2. 렉트만 있음으로 단순한 판별식이 된다. ( Logic 4회 n)
		// 3. 기능에 따른 함수를 넣어주는것이 일인데 전역함수로 넣어준다.//이건 custom obj에서 할일  //여기서는 넣을수 있도록 구현해주는것.
		// 

		// 구별법 1. 섹션분할  1~4사분면으로 선체크 or DC를 충돌체로만들어 사전 충돌체크를 하던지 말던지...
		// 구별법 2. 그룹링크 상태 -> 1번과 2번은 상호간에 링크되어있다 안되어있다. 이런것들을 확인하고 할것.

	};


public:
	CollisionManager();
	~CollisionManager();
};

