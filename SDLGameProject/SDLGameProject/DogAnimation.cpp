#include "DogAnimation.h"
#include "Stage.h"



// 텍스처 추가
void DogAnimation::AddTexture()
{
	if (dog_move_type != pre_move_type)
	{
		pre_move_type = dog_move_type;
		dog_animation.clear();

		switch (dog_move_type)
		{
		case 1://left walk
		case 2://right walk
			dog_animation.push_back({ 127,1243,208,204 });
			dog_animation.push_back({ 351,1243,208,204 });
			dog_animation.push_back({ 579,1243,208,204 });
			dog_animation.push_back({ 801,1243,208,204 });
			dog_animation.push_back({ 1030,1243,208,204 });
			dog_animation.push_back({ 1258,1243,208,204 });
			break;
		case 3://left jump
		case 4://right jump
			dog_animation.push_back({ 123,1475,208,182 });
			break;
		case 5://death left
		case 6://death right
			dog_animation.push_back({ 826, 1482, 175, 181 });
			break;
		case 7://skill left(sniff)
		case 8://skill right(sniff)
			dog_animation.push_back({ 148,1697,159,197 });
			dog_animation.push_back({ 148,1697,159,197 });
			dog_animation.push_back({ 148,1697,159,197 });
			dog_animation.push_back({ 372,1697,159,197 });
			dog_animation.push_back({ 372,1697,159,197 });
			dog_animation.push_back({ 372,1697,159,197 });
			break;
		case 9://box_collide left
		case 10://box_collide right
			dog_animation.push_back({ 120,1941,160,178 });
			dog_animation.push_back({ 120,1941,160,178 });
			dog_animation.push_back({ 120,1941,160,178 });
			dog_animation.push_back({ 346,1941,160,178 });
			dog_animation.push_back({ 346,1941,160,178 });
			dog_animation.push_back({ 346,1941,160,178 });
			break;
		case 11://left idle
		case 12://right idle
			dog_animation.push_back({ 151,1011,162,186 });
			dog_animation.push_back({ 151,1011,162,186 });
			dog_animation.push_back({ 151,1011,162,186 });
			dog_animation.push_back({ 151,1011,162,186 });
			dog_animation.push_back({ 151,1011,162,186 });

			dog_animation.push_back({ 1264,1011,162,186 });
			dog_animation.push_back({ 1264,1011,162,186 });
			dog_animation.push_back({ 1264,1011,162,186 });
			dog_animation.push_back({ 1264,1011,162,186 });
			dog_animation.push_back({ 1264,1011,162,186 });
			break;
		}
	}
}