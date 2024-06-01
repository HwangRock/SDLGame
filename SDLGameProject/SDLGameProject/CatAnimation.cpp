#include "CatAnimation.h"
#include "Stage.h"



// 텍스처 추가
void CatAnimation::AddTexture()
{
	if (cat_move_type != pre_move_type)
	{
		pre_move_type = cat_move_type;
		cat_animation.clear();

		switch (cat_move_type)
		{
		case 1://left walk
		case 2://right walk
			cat_animation.push_back({ 131,309,208,219 });
			cat_animation.push_back({ 343,309,208,219 });
			cat_animation.push_back({ 570,309,208,219 });
			cat_animation.push_back({ 798,309,208,219 });
			cat_animation.push_back({ 1019,309,208,219 });
			cat_animation.push_back({ 1253,309,208,219 });
			break;
		case 3://left jump
		case 4://right jump
			cat_animation.push_back({ 124,538,204,206 });
			break;
		case 5://death left
		case 6://death right
			cat_animation.push_back({ 573,776,199,220 });
			break;
		case 7://skill left
		case 8://skill right
			cat_animation.push_back({ 157,812,148,123 });
			cat_animation.push_back({ 382,812,148,123 });
			break;
		case 9://left climb
		case 10://right climb
			cat_animation.push_back({ 589,555,189,200 });
			cat_animation.push_back({ 815,555,189,200 });
			cat_animation.push_back({ 1040,555,189,200 });
			cat_animation.push_back({ 1271,555,189,200 });
			cat_animation.push_back({ 1487,555,189,200 });
			cat_animation.push_back({ 1714,555,189,200 });
			break;
		case 11://left idle
		case 12://right idle
			cat_animation.push_back({ 141,75,172,219 });
			cat_animation.push_back({ 141,75,172,219 });
			cat_animation.push_back({ 141,75,172,219 });
			cat_animation.push_back({ 818,75,172,219 });
			cat_animation.push_back({ 1047,75,172,219 });
			cat_animation.push_back({ 1274,75,172,219 });
			cat_animation.push_back({ 1495,75,172,219 });
			cat_animation.push_back({ 1714,75,172,219 });
			cat_animation.push_back({ 1947,75,172,219 });
			break;
		}
	}
}

