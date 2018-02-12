#include "stdafx.h"
#include <vector>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <iostream>

// borrowed heavily from: https://gist.github.com/lawliet89/4106929

int random_number(int start, int end); // Generate a number between start and end

template <typename Iterator>
void quick_sort(Iterator start, Iterator end)
{
	const int size = (end - start);

	if (size <= 0)
		return; // Base case

	// Partition - in place partitioning that involves only swapping
	// https://class.coursera.org/algo/lecture/preview/22 - O(n) time with no extra memory++
	/*
	Assume pivot is first element of array
	Otherwise swap pivot with first element

	Idea: Array A is in this form
	pivot | < p | > p | unpartitioned/unseen

	Let i = index of the first item > p
	Let j = index of the first item unpartitioned

	Let i = 1
	Let j = 1
	Let p = pivot value

	for j < size
	if A[i] < p
	swap A[j] with A[i]
	i++
	swap A[0] with A[i-1]
	*/
	const auto random_pivot_index = random_number(0, size);
	typename std::iterator_traits<Iterator>::value_type pivot = *(start + random_pivot_index);

	if (random_pivot_index != 0)
		std::swap(*(start + random_pivot_index), *start);

	auto i = 1;

	for (auto j = 1; j < size; j++)
	{
		if (*(start + j) < pivot)
		{
			std::swap(*(start + j), *(start + i));
			i++;
		}
	}

	std::swap(*start, *(start + i - 1));

	quick_sort(start, start + i - 1);
	quick_sort(start + i, end);
}

int main()
{
	std::vector<unsigned int> input = {
		557, 320, 318, 606, 477, 812, 961, 254, 430, 334, 543, 360, 783, 378, 599, 177, 198, 80, 182, 292, 766, 507, 813, 843,
		484, 792, 138, 1, 904, 141, 548, 420, 964, 711, 809, 100, 778, 20, 686, 530, 896, 804, 868, 845, 875, 302, 646, 728,
		542, 805, 863, 157, 248, 629, 802, 435, 278, 407, 184, 833, 445, 653, 113, 79, 578, 486, 962, 535, 439, 176, 313, 592,
		741, 363, 202, 24, 505, 776, 955, 136, 871, 119, 799, 159, 213, 9, 506, 317, 846, 219, 508, 147, 447, 607, 32, 350,
		357, 54, 36, 527, 339, 675, 293, 353, 547, 241, 158, 735, 171, 102, 108, 196, 697, 840, 670, 464, 125, 417, 519, 153,
		873, 133, 127, 752, 779, 55, 586, 285, 786, 525, 895, 82, 924, 537, 730, 803, 801, 862, 865, 392, 870, 114, 556, 377,
		858, 488, 884, 223, 797, 235, 389, 719, 441, 596, 373, 163, 13, 402, 497, 354, 393, 72, 680, 90, 210, 25, 249, 259,
		908, 34, 767, 168, 742, 822, 912, 724, 597, 715, 485, 561, 476, 140, 453, 510, 386, 264, 442, 328, 502, 986, 769, 421,
		579, 827, 63, 498, 201, 618, 461, 930, 84, 790, 396, 368, 128, 433, 754, 796, 515, 193, 882, 183, 35, 546, 999, 500,
		116, 633, 261, 713, 877, 911, 156, 844, 101, 692, 940, 496, 98, 656, 427, 814, 589, 45, 449, 331, 583, 231, 888, 712,
		771, 825, 197, 26, 372, 118, 657, 263, 314, 757, 823, 565, 444, 820, 780, 237, 660, 344, 289, 836, 603, 234, 103, 189,
		729, 362, 848, 943, 130, 74, 985, 651, 994, 85, 419, 998, 110, 160, 545, 847, 454, 390, 900, 343, 626, 678, 619, 782,
		269, 104, 795, 988, 121, 647, 946, 77, 61, 677, 938, 361, 939, 166, 107, 310, 512, 96, 973, 570, 308, 552, 186, 630,
		929, 770, 178, 375, 11, 146, 838, 438, 785, 448, 609, 679, 997, 524, 279, 923, 132, 760, 763, 342, 165, 621, 978, 246,
		751, 658, 777, 482, 638, 131, 288, 682, 120, 671, 891, 180, 227, 927, 717, 271, 296, 815, 710, 272, 517, 615, 571,
		395, 577, 689, 818, 209, 854, 337, 902, 672, 18, 639, 954, 616, 894, 315, 379, 726, 115, 731, 299, 663, 691, 725, 909,
		187, 2, 220, 232, 49, 142, 274, 949, 148, 349, 585, 800, 73, 99, 398, 207, 839, 305, 422, 247, 811, 429, 694, 668,
		513, 635, 541, 208, 298, 641, 214, 14, 406, 57, 834, 708, 746, 7, 567, 906, 175, 864, 316, 704, 475, 522, 325, 523,
		95, 352, 17, 762, 222, 474, 887, 857, 129, 480, 806, 52, 975, 957, 370, 600, 347, 632, 740, 92, 855, 340, 455, 970,
		401, 568, 465, 66, 67, 6, 405, 28, 266, 705, 993, 643, 68, 914, 701, 446, 270, 253, 550, 739, 972, 27, 143, 329, 466,
		326, 824, 410, 926, 544, 716, 967, 819, 566, 8, 418, 878, 590, 203, 457, 659, 42, 205, 634, 837, 580, 83, 324, 408,
		781, 499, 312, 5, 971, 625, 384, 950, 655, 346, 720, 145, 934, 706, 190, 768, 155, 685, 273, 667, 478, 889, 440, 521,
		172, 212, 333, 662, 718, 901, 915, 112, 573, 584, 257, 436, 50, 798, 236, 501, 965, 170, 576, 424, 559, 284, 932, 306,
		533, 921, 979, 137, 126, 423, 105, 910, 479, 76, 12, 765, 551, 829, 412, 456, 173, 194, 925, 852, 835, 300, 893, 29,
		200, 526, 335, 192, 673, 304, 830, 695, 883, 696, 89, 613, 693, 311, 903, 514, 645, 536, 581, 321, 745, 832, 491, 117,
		750, 636, 432, 44, 898, 319, 531, 593, 821, 644, 327, 987, 734, 409, 714, 960, 492, 358, 59, 21, 920, 245, 224, 371,
		31, 503, 942, 681, 549, 631, 60, 604, 761, 404, 963, 774, 995, 980, 388, 620, 37, 69, 280, 842, 736, 277, 204, 969,
		256, 617, 683, 39, 518, 471, 174, 355, 394, 666, 595, 71, 747, 369, 467, 382, 831, 322, 788, 861, 890, 553, 255, 111,
		534, 881, 472, 991, 787, 437, 959, 191, 931, 211, 772, 367, 591, 287, 951, 555, 416, 144, 493, 699, 332, 605, 952,
		290, 47, 167, 665, 385, 789, 179, 216, 528, 383, 885, 654, 737, 859, 684, 869, 164, 16, 841, 463, 206, 808, 434, 649,
		365, 221, 983, 937, 233, 856, 650, 251, 918, 139, 976, 936, 661, 958, 41, 495, 19, 380, 867, 992, 748, 702, 922, 688,
		669, 431, 391, 450, 88, 242, 698, 97, 413, 244, 941, 338, 348, 623, 250, 258, 880, 614, 150, 933, 281, 109, 33, 23,
		489, 64, 230, 415, 134, 22, 569, 330, 749, 948, 966, 351, 532, 282, 611, 874, 899, 733, 291, 451, 494, 303, 608, 886,
		652, 700, 612, 403, 58, 723, 759, 297, 93, 773, 860, 849, 400, 707, 529, 690, 195, 218, 283, 575, 907, 106, 458, 564,
		387, 3, 539, 817, 323, 185, 56, 399, 336, 267, 65, 239, 538, 40, 374, 87, 913, 753, 851, 853, 687, 764, 968, 481, 51,
		511, 53, 598, 516, 268, 275, 487, 917, 188, 473, 15, 294, 624, 38, 124, 554, 540, 664, 674, 468, 977, 48, 62, 866, 91,
		622, 919, 982, 743, 640, 10, 755, 879, 462, 956, 928, 676, 152, 262, 594, 1000, 4, 876, 411, 721, 990, 483, 794, 828,
		563, 588, 744, 149, 376, 775, 276, 452, 509, 225, 86, 582, 572, 78, 504, 217, 307, 892, 428, 758, 562, 944, 215, 81,
		732, 238, 953, 381, 558, 43, 560, 240, 199, 162, 627, 610, 309, 602, 601, 181, 989, 490, 722, 826, 459, 648, 154, 75,
		265, 738, 426, 228, 981, 169, 935, 252, 295, 945, 703, 469, 70, 916, 810, 727, 784, 366, 996, 30, 414, 628, 286, 46,
		135, 816, 574, 460, 807, 637, 151, 364, 301, 974, 947, 359, 756, 229, 397, 897, 850, 872, 123, 587, 226, 161, 984,
		356, 470, 642, 345, 443, 709, 341, 260, 793, 122, 425, 520, 791, 94, 905, 243
	};

	quick_sort(input.begin(), input.end());

	return 0;
}

// Generate a number between start and end
int random_number(const int start, const int end)
{
	// Seed the randomiser
	srand(time(nullptr));

	return rand() % end + start;
}
