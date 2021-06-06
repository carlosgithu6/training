#include <iostream>
#include <vector>
#include<algorithm>
#include<chrono>
#include <random>
#include "lest.hpp"
using namespace std;
using namespace std::chrono;

class Meeting
{
private:
    // number of 30 min blocks past 9:00 am
    unsigned int startTime_;
    unsigned int endTime_;

public:
    Meeting() :
        startTime_(0),
        endTime_(0)
    {
    }

    Meeting(unsigned int startTime, unsigned int endTime) :
        startTime_(startTime),
        endTime_(endTime)
    {
    }

    unsigned int getStartTime() const
    {
        return startTime_;
    }

    void setStartTime(unsigned int startTime)
    {
        startTime_ = startTime;
    }

    unsigned int getEndTime() const
    {
        return endTime_;
    }

    void setEndTime(unsigned int endTime)
    {
        endTime_ = endTime;
    }

    bool operator==(const Meeting& other) const
    {
        return
            startTime_ == other.startTime_
            && endTime_ == other.endTime_;
    }
    bool operator<(const Meeting& other) const
    {
        return startTime_ < other.startTime_;
    }
    bool operator>(const Meeting& other) const
    {
        return startTime_ > other.startTime_;
    }
    bool isOverLapped(const Meeting other)const
    {
        return endTime_ >= other.startTime_;
    }
};
bool compareMeetingsByStartTime(
    const Meeting& firstMeeting,
    const Meeting& secondMeeting)
{
    return firstMeeting.getStartTime() < secondMeeting.getStartTime();
}

//O(nlg(n)) Curso
vector<Meeting> mergeRangesV2(const vector<Meeting>& meetings)
{
    // sort by start time
    vector<Meeting> sortedMeetings(meetings);
    sort(sortedMeetings.begin(), sortedMeetings.end(), compareMeetingsByStartTime);

    // initialize mergedMeetings with the earliest meeting
    vector<Meeting> mergedMeetings;
    mergedMeetings.push_back(sortedMeetings.front());

    for (const Meeting& currentMeeting : sortedMeetings) {
        Meeting& lastMergedMeeting = mergedMeetings.back();

        if (currentMeeting.getStartTime()
            <= lastMergedMeeting.getEndTime()) {
            // if the current meeting overlaps with the last merged meeting, use the
            // later end time of the two
            lastMergedMeeting.setEndTime(max(lastMergedMeeting.getEndTime(),
                currentMeeting.getEndTime()));
        }
        else {
            // add the current meeting since it doesn't overlap
            mergedMeetings.push_back(currentMeeting);
        }
    }

    return mergedMeetings;
}

//O(n^2) Mio erase
vector<Meeting> mergeRangesV1(const vector<Meeting>& meetings)
{
    auto i_meetings = meetings;

    sort(i_meetings.begin(), i_meetings.end(), [](Meeting item1, Meeting item2) {
        return item1 < item2;
       });

    
    size_t pend = 0;
    while (pend<i_meetings.size())
    {
        if (pend + 1 < i_meetings.size() && i_meetings[pend].isOverLapped(i_meetings[pend + 1]))
        {
            Meeting _m(i_meetings[pend].getStartTime(),
                          max(i_meetings[pend].getEndTime(), i_meetings[pend+1].getEndTime()));
            i_meetings.erase(i_meetings.begin() + (pend));
            i_meetings[pend] = _m;
        }
        else
            pend++;
       
    }
    return i_meetings;
}
//O(n^2) Mio Inplace. space(1) 
void mergeRangesV3(vector<Meeting>& meetings)
{
    sort(meetings.begin(), meetings.end(), [](Meeting item1, Meeting item2) {
        return item1 < item2;
       });

    size_t pend = 0;
    while (pend<meetings.size())
    {
        if (pend + 1 < meetings.size() && meetings[pend].isOverLapped(meetings[pend + 1]))
        {
            Meeting _m(meetings[pend].getStartTime(),
                          max(meetings[pend].getEndTime(), meetings[pend+1].getEndTime()));
            meetings.erase(meetings.begin() + (pend));
            meetings[pend] = _m;
        }
        else
            pend++;
    }
 
}

//O(nlg(n)) Mio
vector<Meeting> mergeRanges(const vector<Meeting>& meetings)
{
    auto i_meetings = meetings;

    sort(i_meetings.begin(), i_meetings.end(), [](Meeting item1, Meeting item2) {
        return item1 < item2;
        });

    vector<Meeting> result;
    for (size_t i = 0;i < i_meetings.size();i++)
    {
       
        if ((i+1< i_meetings.size()) && i_meetings[i].isOverLapped(i_meetings[i + 1]))
        {
            Meeting& _m = i_meetings[i];
            _m.setStartTime(i_meetings[i].getStartTime());
            _m.setEndTime( max(i_meetings[i].getEndTime(), i_meetings[i + 1].getEndTime()));
            i_meetings[i + 1] = _m;
        }
        else 
        {
            result.push_back(i_meetings[i]);
        }
    }
    return result;
}
// tests



/*
Bonus
    What if we did have an upper bound on the input values?
    Could we improve our runtime? Would it cost us memory?
    Could we do this "in place" on the input vector and save some space?
    What are the pros and cons of doing this in place?
 
*/

const lest::test tests[] = {
    {CASE("meetings overlap") {
        const auto meetings = vector<Meeting> {Meeting(1, 3), Meeting(2, 4)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 4)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings touch") {
        const auto meetings = vector<Meeting> {Meeting(5, 6), Meeting(6, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(5, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meeting contains other meeting") {
        const auto meetings = vector<Meeting> {Meeting(1, 8), Meeting(2, 5)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings stay separate") {
        const auto meetings = vector<Meeting> {Meeting(1, 3), Meeting(4, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 3), Meeting(4, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("multiple merged meetings") {
        const auto meetings = vector<Meeting> {Meeting(1, 4), Meeting(2, 5), Meeting(5, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("meetings not sorted") {
        const auto meetings = vector<Meeting> {Meeting(5, 8), Meeting(1, 4), Meeting(6, 8)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 4), Meeting(5, 8)};
        EXPECT(actual == expected);
    }},

    {CASE("one long meeting contains smaller meetings") {
        const auto meetings = vector<Meeting> {Meeting(1, 10), Meeting(2, 5), Meeting(6, 8),
            Meeting(9, 10), Meeting(10, 12)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(1, 12)};
        EXPECT(actual == expected);
    }},

    {CASE("sample input") {
        const auto meetings = vector<Meeting> {Meeting(0, 1), Meeting(3, 5), Meeting(4, 8),
            Meeting(10, 12), Meeting(9, 10)};
        const auto actual = mergeRanges(meetings);
        const auto expected = vector<Meeting> {Meeting(0, 1), Meeting(3, 8), Meeting(9, 12)};
        EXPECT(actual == expected);
    }},
};

//int main(int argc, char** argv)
//{
//    return lest::run(tests, argc, argv);
//}



int main()
{

   /*auto const meetings1 = vector<Meeting>{ Meeting(1, 12), Meeting(1, 3),Meeting(5,7),Meeting(14, 15),Meeting(4, 8),Meeting(3,6),Meeting(13, 14),Meeting(2, 9),Meeting(7, 14),Meeting(4, 6),Meeting(8, 8) };
   auto const meetings2 = vector<Meeting>{ Meeting(1, 12), Meeting(1, 3),Meeting(5,7),Meeting(14, 15),Meeting(4, 8),Meeting(3,6),Meeting(13, 14),Meeting(2, 9),Meeting(7, 14),Meeting(4, 6),Meeting(8, 8) };
   auto       meetings3 = vector<Meeting>{ Meeting(1, 12), Meeting(1, 3),Meeting(5,7),Meeting(14, 15),Meeting(4, 8),Meeting(3,6),Meeting(13, 14),Meeting(2, 9),Meeting(7, 14),Meeting(4, 6),Meeting(8, 8) };*/

   auto  const meetings1 = vector<Meeting>{Meeting(1, 12),Meeting(1,3),Meeting(5,7),Meeting(14,15),Meeting(4,8),Meeting(3,6),Meeting(13,14),Meeting(2, 9),Meeting(7, 14),Meeting(4, 6),Meeting(8, 8),Meeting(9899, 27000), Meeting(7394, 28322), Meeting(22300, 24431), Meeting(12385, 12859), Meeting(3659, 30534), Meeting(1274, 25378), Meeting(15264, 25022), Meeting(2570, 13069), Meeting(16879, 25465), Meeting(4215, 8218), Meeting(2831, 9095), Meeting(6467, 22802), Meeting(23378, 24959), Meeting(14062, 29281), Meeting(8029, 12477), Meeting(5575, 28570), Meeting(2557, 15149), Meeting(26106, 32452), Meeting(12651, 13337), Meeting(15147, 27028), Meeting(1577, 30949), Meeting(1291, 12594), Meeting(25177, 30930), Meeting(16237, 19963), Meeting(13164, 14818), Meeting(16867, 17214), Meeting(4439, 32707), Meeting(8537, 11383), Meeting(22468, 22574), Meeting(11449, 21250), Meeting(20720, 21799), Meeting(10018, 16831), Meeting(17489, 31466), Meeting(5303, 6554), Meeting(17446, 24184), Meeting(9256, 13527), Meeting(6041, 28424), Meeting(12710, 13435), Meeting(7070, 26693), Meeting(10681, 18762), Meeting(11058, 13475), Meeting(11926, 28109), Meeting(1714, 8226), Meeting(19631, 23699), Meeting(12782, 15316), Meeting(16181, 23056), Meeting(17910, 19745), Meeting(20108, 24569), Meeting(23770, 31403), Meeting(11275, 24290), Meeting(10972, 31530), Meeting(5052, 25938), Meeting(25519, 32714), Meeting(8826, 22017), Meeting(835, 6773), Meeting(18896, 23498), Meeting(10899, 18332), Meeting(1082, 4299), Meeting(1694, 32090), Meeting(26, 14913), Meeting(9386, 13509), Meeting(2209, 27130), Meeting(13016, 18036), Meeting(25132, 26575), Meeting(10244, 30517), Meeting(7297, 30912), Meeting(28384, 28943), Meeting(4655, 25710), Meeting(16864, 21223), Meeting(29161, 29712), Meeting(4038, 22290), Meeting(26055, 28437), Meeting(25943, 27699), Meeting(12512, 21720), Meeting(4838, 25037), Meeting(1301, 10677), Meeting(5402, 30992), Meeting(1263, 31615), Meeting(11751, 17661), Meeting(10953, 31787), Meeting(27172, 30051), Meeting(6559, 18016), Meeting(5836, 25020), Meeting(5779, 9414), Meeting(21059, 32632), Meeting(16966, 23814), Meeting(1275, 20601), Meeting(16210, 26918), Meeting(25413, 32722), Meeting(9847, 22197), Meeting(3720, 28334), Meeting(916, 10413), Meeting(27545, 29578), Meeting(3526, 8615), Meeting(26520, 27256), Meeting(11887, 31408), Meeting(13011, 26316), Meeting(5697, 24468), Meeting(8936, 11545), Meeting(4520, 5965), Meeting(42, 2396), Meeting(6691, 29442), Meeting(16966, 21878), Meeting(19626, 29558), Meeting(39, 17376), Meeting(3826, 29471), Meeting(5910, 17050), Meeting(25700, 27658), Meeting(2660, 19750), Meeting(207, 25467), Meeting(11825, 29391), Meeting(11338, 32740), Meeting(16089, 18393), Meeting(4868, 18033), Meeting(10107, 22286), Meeting(12938, 26262), Meeting(9105, 16325), Meeting(4994, 31919), Meeting(15269, 22587), Meeting(22589, 23364), Meeting(24005, 27587), Meeting(10456, 27199), Meeting(6593, 25746), Meeting(5203, 7344), Meeting(2063, 12928), Meeting(15362, 16305), Meeting(16144, 25300), Meeting(4577, 29166), Meeting(17149, 21744), Meeting(13143, 21046), Meeting(1923, 19663), Meeting(8454, 15493), Meeting(16715, 32016), Meeting(8753, 24307), Meeting(9250, 17391), Meeting(7942, 29513), Meeting(10721, 22248), Meeting(10667, 32066), Meeting(18639, 20094), Meeting(10929, 12541), Meeting(1135, 32499), Meeting(6724, 12309), Meeting(24302, 28670), Meeting(188, 31479), Meeting(4616, 25723), Meeting(5942, 21913), Meeting(2656, 20266), Meeting(16711, 32412), Meeting(19156, 26355), Meeting(1716, 10742), Meeting(5954, 21306), Meeting(854, 24800), Meeting(4683, 7347), Meeting(19359, 24742), Meeting(7750, 27273), Meeting(22997, 31819), Meeting(25976, 32698), Meeting(15267, 24906), Meeting(8806, 14305), Meeting(2343, 20068), Meeting(3296, 30403), Meeting(6472, 24736), Meeting(20365, 32469), Meeting(9687, 23555), Meeting(4057, 31983), Meeting(11446, 15041), Meeting(14052, 29296), Meeting(13362, 29879), Meeting(141, 20680), Meeting(12561, 22717), Meeting(5586, 22839), Meeting(959, 6730), Meeting(5638, 13611), Meeting(20482, 26651), Meeting(12707, 31876), Meeting(1120, 20133), Meeting(1779, 20873), Meeting(6198, 30549), Meeting(16408, 27378), Meeting(5438, 18403), Meeting(1767, 20393), Meeting(989, 25178), Meeting(7248, 20087), Meeting(5808, 16742), Meeting(14302, 25887), Meeting(3852, 3884), Meeting(801, 6922), Meeting(20292, 22997), Meeting(2440, 20229), Meeting(24283, 31167), Meeting(7210, 20624), Meeting(16794, 24632), Meeting(6620, 11363), Meeting(4544, 30375), Meeting(2874, 5240), Meeting(2562, 31076), Meeting(3975, 16070), Meeting(26059, 32721), Meeting(14393, 29902), Meeting(8357, 16586), Meeting(8985, 23567), Meeting(8094, 8340), Meeting(14295, 27278), Meeting(4330, 21525), Meeting(13021, 13722), Meeting(21823, 24021), Meeting(5586, 23136), Meeting(7213, 21365), Meeting(9434, 12611), Meeting(6980, 7144), Meeting(10245, 27781), Meeting(12973, 27565), Meeting(6717, 20723), Meeting(6203, 32284), Meeting(422, 9372), Meeting(11799, 32395), Meeting(12926, 27270), Meeting(2831, 13149), Meeting(6687, 9672), Meeting(20796, 26161), Meeting(17961, 18422), Meeting(11682, 18073), Meeting(22418, 29483), Meeting(926, 23687), Meeting(543, 18213), Meeting(28853, 30165), Meeting(1087, 9602), Meeting(24039, 29127), Meeting(3156, 20502), Meeting(18627, 22611), Meeting(6175, 11402), Meeting(2531, 3965), Meeting(3862, 17580), Meeting(24944, 32297), Meeting(5068, 24341), Meeting(12626, 19647), Meeting(7165, 30905), Meeting(5838, 10736), Meeting(4469, 13591), Meeting(17615, 19003), Meeting(10747, 28393), Meeting(26017, 29583), Meeting(1713, 12504), Meeting(21305, 24022), Meeting(7698, 27415), Meeting(4368, 5498), Meeting(3306, 8578), Meeting(6194, 26408), Meeting(2216, 12265), Meeting(10641, 14548), Meeting(6852, 21694), Meeting(6816, 29693), Meeting(5004, 27613), Meeting(20509, 25906), Meeting(1061, 25002), Meeting(13525, 23342), Meeting(8185, 22070), Meeting(23839, 27824), Meeting(4589, 15395), Meeting(4812, 16740), Meeting(18069, 18953), Meeting(19096, 29899), Meeting(6935, 9891), Meeting(299, 11539), Meeting(17150, 21926), Meeting(15249, 16882), Meeting(18673, 22794), Meeting(19266, 27517), Meeting(16018, 19160), Meeting(28271, 30766), Meeting(9363, 15907), Meeting(1267, 27084), Meeting(5272, 13756), Meeting(28300, 31883), Meeting(221, 13483), Meeting(6904, 10183), Meeting(8115, 10820), Meeting(182, 31643), Meeting(5670, 32415), Meeting(12535, 15558), Meeting(13790, 17225), Meeting(24496, 32754), Meeting(21059, 23609), Meeting(3015, 12385), Meeting(13574, 28901), Meeting(6312, 18607), Meeting(22103, 22810), Meeting(12317, 32464), Meeting(18153, 28570), Meeting(4058, 22494), Meeting(10489, 17702), Meeting(7451, 24915), Meeting(20873, 29407), Meeting(12585, 13531), Meeting(14327, 15813), Meeting(9673, 22461), Meeting(11537, 27196), Meeting(3896, 8249), Meeting(13958, 15023), Meeting(24932, 31524), Meeting(13211, 19580), Meeting(16180, 27386), Meeting(1961, 28295), Meeting(24539, 27747), Meeting(8944, 28923), Meeting(9540, 15645), Meeting(3400, 8894), Meeting(11859, 21144), Meeting(7763, 10443), Meeting(9501, 22543), Meeting(12541, 14802), Meeting(11173, 27046), Meeting(8165, 18527), Meeting(10289, 25456), Meeting(8344, 23999), Meeting(8372, 11483), Meeting(2943, 28580), Meeting(16473, 32121), Meeting(12545, 26657), Meeting(18604, 29110), Meeting(12918, 16711), Meeting(13906, 16242), Meeting(29065, 31204), Meeting(21181, 26923), Meeting(115, 20696), Meeting(20314, 27422), Meeting(18735, 26878), Meeting(7898, 17889), Meeting(7598, 31631), Meeting(3647, 31907), Meeting(9796, 31692), Meeting(23096, 25268), Meeting(20824, 24805), Meeting(10195, 26912), Meeting(21831, 23857), Meeting(28116, 30517), Meeting(19430, 21315), Meeting(20357, 25868), Meeting(7730, 10834), Meeting(7208, 31979), Meeting(3303, 3382), Meeting(6868, 29637), Meeting(6979, 9924), Meeting(8197, 29568), Meeting(254, 3691), Meeting(21143, 26957), Meeting(508, 24213), Meeting(9433, 11128), Meeting(12781, 18086), Meeting(7120, 29809), Meeting(7011, 30975), Meeting(13793, 31234), Meeting(14111, 24641), Meeting(2236, 8377), Meeting(21386, 21488), Meeting(12361, 18900), Meeting(10805, 26256), Meeting(4695, 20456), Meeting(24610, 26732), Meeting(6553, 10176), Meeting(7353, 19260), Meeting(16707, 25620), Meeting(30721, 32263), Meeting(16831, 25518), Meeting(11089, 11783), Meeting(13106, 27962), Meeting(20029, 31443), Meeting(10048, 20319), Meeting(12734, 25554), Meeting(289, 22017), Meeting(15014, 26075), Meeting(4096, 10422), Meeting(2518, 21149), Meeting(10754, 27673), Meeting(14142, 29874), Meeting(16323, 17958), Meeting(5698, 25042), Meeting(24355, 26312), Meeting(24058, 30895), Meeting(7134, 13841), Meeting(6766, 32077), Meeting(19766, 20717), Meeting(13813, 23741), Meeting(5139, 30940), Meeting(13091, 22470), Meeting(6381, 8027), Meeting(15723, 18012), Meeting(823, 9046), Meeting(1333, 22306), Meeting(13841, 19657), Meeting(12417, 23004), Meeting(945, 27956), Meeting(3623, 16078), Meeting(11909, 26059), Meeting(19048, 25658), Meeting(6288, 19192), Meeting(3842, 8170), Meeting(6826, 17261), Meeting(4524, 22988), Meeting(3133, 12869), Meeting(19906, 21211), Meeting(16595, 32453), Meeting(762, 22148), Meeting(13591, 22589), Meeting(4826, 5318), Meeting(6473, 24550), Meeting(1407, 13449), Meeting(2633, 32690), Meeting(11813, 32163), Meeting(3604, 28962), Meeting(6961, 18161), Meeting(3483, 21069), Meeting(5848, 15171), Meeting(14865, 29416), Meeting(2370, 31824), Meeting(22557, 30441), Meeting(17602, 29464), Meeting(2671, 19792), Meeting(8296, 16748), Meeting(5320, 6642), Meeting(10264, 25960), Meeting(3840, 13001), Meeting(19871, 31614), Meeting(1004, 19695), Meeting(16814, 20494), Meeting(2886, 25094), Meeting(15132, 21054), Meeting(20259, 30108), Meeting(12087, 15680), Meeting(23753, 29358), Meeting(7986, 11261), Meeting(618, 30660), Meeting(2866, 24224), Meeting(9015, 16441), Meeting(8811, 29326), Meeting(21873, 28413), Meeting(14835, 23346), Meeting(2496, 5015), Meeting(4616, 27591), Meeting(6317, 9354), Meeting(20400, 25682), Meeting(23961, 24490), Meeting(5495, 28419), Meeting(9399, 25350), Meeting(19115, 22151), Meeting(13435, 19911), Meeting(7462, 16731), Meeting(11336, 18274), Meeting(15734, 19005), Meeting(6713, 8993), Meeting(12747, 29013), Meeting(4583, 28218), Meeting(6431, 25762), Meeting(974, 16573), Meeting(4778, 17314), Meeting(1291, 14770), Meeting(273, 32441), Meeting(19653, 30983), Meeting(9453, 11972), Meeting(12050, 26496), Meeting(23626, 28464), Meeting(828, 30414), Meeting(1458, 5124), Meeting(9737, 16670), Meeting(1377, 5454), Meeting(17526, 29623), Meeting(14499, 15314), Meeting(6732, 28983), Meeting(22046, 26723), Meeting(13123, 13521), Meeting(1110, 1135), Meeting(23954, 24461), Meeting(1803, 4921), Meeting(5157, 16751), Meeting(3086, 13092), Meeting(8776, 13477), Meeting(16102, 16282), Meeting(1556, 23915), Meeting(13086, 23521), Meeting(8993, 21815), Meeting(545, 25043), Meeting(16289, 24312), Meeting(2146, 8394), Meeting(12149, 22735), Meeting(7817, 26640), Meeting(22575, 22642), Meeting(16445, 17197), Meeting(8649, 30274), Meeting(10129, 14608), Meeting(2829, 10305), Meeting(1006, 16187), Meeting(14640, 27983), Meeting(4934, 29229), Meeting(9721, 15703), Meeting(13449, 21507), Meeting(21337, 28563), Meeting(1372, 22358), Meeting(13702, 32199), Meeting(17528, 21753), Meeting(9002, 27882), Meeting(1623, 14047)};
   auto  const meetings2 = vector<Meeting>{Meeting(1, 12),Meeting(1,3),Meeting(5,7),Meeting(14,15),Meeting(4,8),Meeting(3,6),Meeting(13,14),Meeting(2, 9),Meeting(7, 14),Meeting(4, 6),Meeting(8, 8),Meeting(9899, 27000), Meeting(7394, 28322), Meeting(22300, 24431), Meeting(12385, 12859), Meeting(3659, 30534), Meeting(1274, 25378), Meeting(15264, 25022), Meeting(2570, 13069), Meeting(16879, 25465), Meeting(4215, 8218), Meeting(2831, 9095), Meeting(6467, 22802), Meeting(23378, 24959), Meeting(14062, 29281), Meeting(8029, 12477), Meeting(5575, 28570), Meeting(2557, 15149), Meeting(26106, 32452), Meeting(12651, 13337), Meeting(15147, 27028), Meeting(1577, 30949), Meeting(1291, 12594), Meeting(25177, 30930), Meeting(16237, 19963), Meeting(13164, 14818), Meeting(16867, 17214), Meeting(4439, 32707), Meeting(8537, 11383), Meeting(22468, 22574), Meeting(11449, 21250), Meeting(20720, 21799), Meeting(10018, 16831), Meeting(17489, 31466), Meeting(5303, 6554), Meeting(17446, 24184), Meeting(9256, 13527), Meeting(6041, 28424), Meeting(12710, 13435), Meeting(7070, 26693), Meeting(10681, 18762), Meeting(11058, 13475), Meeting(11926, 28109), Meeting(1714, 8226), Meeting(19631, 23699), Meeting(12782, 15316), Meeting(16181, 23056), Meeting(17910, 19745), Meeting(20108, 24569), Meeting(23770, 31403), Meeting(11275, 24290), Meeting(10972, 31530), Meeting(5052, 25938), Meeting(25519, 32714), Meeting(8826, 22017), Meeting(835, 6773), Meeting(18896, 23498), Meeting(10899, 18332), Meeting(1082, 4299), Meeting(1694, 32090), Meeting(26, 14913), Meeting(9386, 13509), Meeting(2209, 27130), Meeting(13016, 18036), Meeting(25132, 26575), Meeting(10244, 30517), Meeting(7297, 30912), Meeting(28384, 28943), Meeting(4655, 25710), Meeting(16864, 21223), Meeting(29161, 29712), Meeting(4038, 22290), Meeting(26055, 28437), Meeting(25943, 27699), Meeting(12512, 21720), Meeting(4838, 25037), Meeting(1301, 10677), Meeting(5402, 30992), Meeting(1263, 31615), Meeting(11751, 17661), Meeting(10953, 31787), Meeting(27172, 30051), Meeting(6559, 18016), Meeting(5836, 25020), Meeting(5779, 9414), Meeting(21059, 32632), Meeting(16966, 23814), Meeting(1275, 20601), Meeting(16210, 26918), Meeting(25413, 32722), Meeting(9847, 22197), Meeting(3720, 28334), Meeting(916, 10413), Meeting(27545, 29578), Meeting(3526, 8615), Meeting(26520, 27256), Meeting(11887, 31408), Meeting(13011, 26316), Meeting(5697, 24468), Meeting(8936, 11545), Meeting(4520, 5965), Meeting(42, 2396), Meeting(6691, 29442), Meeting(16966, 21878), Meeting(19626, 29558), Meeting(39, 17376), Meeting(3826, 29471), Meeting(5910, 17050), Meeting(25700, 27658), Meeting(2660, 19750), Meeting(207, 25467), Meeting(11825, 29391), Meeting(11338, 32740), Meeting(16089, 18393), Meeting(4868, 18033), Meeting(10107, 22286), Meeting(12938, 26262), Meeting(9105, 16325), Meeting(4994, 31919), Meeting(15269, 22587), Meeting(22589, 23364), Meeting(24005, 27587), Meeting(10456, 27199), Meeting(6593, 25746), Meeting(5203, 7344), Meeting(2063, 12928), Meeting(15362, 16305), Meeting(16144, 25300), Meeting(4577, 29166), Meeting(17149, 21744), Meeting(13143, 21046), Meeting(1923, 19663), Meeting(8454, 15493), Meeting(16715, 32016), Meeting(8753, 24307), Meeting(9250, 17391), Meeting(7942, 29513), Meeting(10721, 22248), Meeting(10667, 32066), Meeting(18639, 20094), Meeting(10929, 12541), Meeting(1135, 32499), Meeting(6724, 12309), Meeting(24302, 28670), Meeting(188, 31479), Meeting(4616, 25723), Meeting(5942, 21913), Meeting(2656, 20266), Meeting(16711, 32412), Meeting(19156, 26355), Meeting(1716, 10742), Meeting(5954, 21306), Meeting(854, 24800), Meeting(4683, 7347), Meeting(19359, 24742), Meeting(7750, 27273), Meeting(22997, 31819), Meeting(25976, 32698), Meeting(15267, 24906), Meeting(8806, 14305), Meeting(2343, 20068), Meeting(3296, 30403), Meeting(6472, 24736), Meeting(20365, 32469), Meeting(9687, 23555), Meeting(4057, 31983), Meeting(11446, 15041), Meeting(14052, 29296), Meeting(13362, 29879), Meeting(141, 20680), Meeting(12561, 22717), Meeting(5586, 22839), Meeting(959, 6730), Meeting(5638, 13611), Meeting(20482, 26651), Meeting(12707, 31876), Meeting(1120, 20133), Meeting(1779, 20873), Meeting(6198, 30549), Meeting(16408, 27378), Meeting(5438, 18403), Meeting(1767, 20393), Meeting(989, 25178), Meeting(7248, 20087), Meeting(5808, 16742), Meeting(14302, 25887), Meeting(3852, 3884), Meeting(801, 6922), Meeting(20292, 22997), Meeting(2440, 20229), Meeting(24283, 31167), Meeting(7210, 20624), Meeting(16794, 24632), Meeting(6620, 11363), Meeting(4544, 30375), Meeting(2874, 5240), Meeting(2562, 31076), Meeting(3975, 16070), Meeting(26059, 32721), Meeting(14393, 29902), Meeting(8357, 16586), Meeting(8985, 23567), Meeting(8094, 8340), Meeting(14295, 27278), Meeting(4330, 21525), Meeting(13021, 13722), Meeting(21823, 24021), Meeting(5586, 23136), Meeting(7213, 21365), Meeting(9434, 12611), Meeting(6980, 7144), Meeting(10245, 27781), Meeting(12973, 27565), Meeting(6717, 20723), Meeting(6203, 32284), Meeting(422, 9372), Meeting(11799, 32395), Meeting(12926, 27270), Meeting(2831, 13149), Meeting(6687, 9672), Meeting(20796, 26161), Meeting(17961, 18422), Meeting(11682, 18073), Meeting(22418, 29483), Meeting(926, 23687), Meeting(543, 18213), Meeting(28853, 30165), Meeting(1087, 9602), Meeting(24039, 29127), Meeting(3156, 20502), Meeting(18627, 22611), Meeting(6175, 11402), Meeting(2531, 3965), Meeting(3862, 17580), Meeting(24944, 32297), Meeting(5068, 24341), Meeting(12626, 19647), Meeting(7165, 30905), Meeting(5838, 10736), Meeting(4469, 13591), Meeting(17615, 19003), Meeting(10747, 28393), Meeting(26017, 29583), Meeting(1713, 12504), Meeting(21305, 24022), Meeting(7698, 27415), Meeting(4368, 5498), Meeting(3306, 8578), Meeting(6194, 26408), Meeting(2216, 12265), Meeting(10641, 14548), Meeting(6852, 21694), Meeting(6816, 29693), Meeting(5004, 27613), Meeting(20509, 25906), Meeting(1061, 25002), Meeting(13525, 23342), Meeting(8185, 22070), Meeting(23839, 27824), Meeting(4589, 15395), Meeting(4812, 16740), Meeting(18069, 18953), Meeting(19096, 29899), Meeting(6935, 9891), Meeting(299, 11539), Meeting(17150, 21926), Meeting(15249, 16882), Meeting(18673, 22794), Meeting(19266, 27517), Meeting(16018, 19160), Meeting(28271, 30766), Meeting(9363, 15907), Meeting(1267, 27084), Meeting(5272, 13756), Meeting(28300, 31883), Meeting(221, 13483), Meeting(6904, 10183), Meeting(8115, 10820), Meeting(182, 31643), Meeting(5670, 32415), Meeting(12535, 15558), Meeting(13790, 17225), Meeting(24496, 32754), Meeting(21059, 23609), Meeting(3015, 12385), Meeting(13574, 28901), Meeting(6312, 18607), Meeting(22103, 22810), Meeting(12317, 32464), Meeting(18153, 28570), Meeting(4058, 22494), Meeting(10489, 17702), Meeting(7451, 24915), Meeting(20873, 29407), Meeting(12585, 13531), Meeting(14327, 15813), Meeting(9673, 22461), Meeting(11537, 27196), Meeting(3896, 8249), Meeting(13958, 15023), Meeting(24932, 31524), Meeting(13211, 19580), Meeting(16180, 27386), Meeting(1961, 28295), Meeting(24539, 27747), Meeting(8944, 28923), Meeting(9540, 15645), Meeting(3400, 8894), Meeting(11859, 21144), Meeting(7763, 10443), Meeting(9501, 22543), Meeting(12541, 14802), Meeting(11173, 27046), Meeting(8165, 18527), Meeting(10289, 25456), Meeting(8344, 23999), Meeting(8372, 11483), Meeting(2943, 28580), Meeting(16473, 32121), Meeting(12545, 26657), Meeting(18604, 29110), Meeting(12918, 16711), Meeting(13906, 16242), Meeting(29065, 31204), Meeting(21181, 26923), Meeting(115, 20696), Meeting(20314, 27422), Meeting(18735, 26878), Meeting(7898, 17889), Meeting(7598, 31631), Meeting(3647, 31907), Meeting(9796, 31692), Meeting(23096, 25268), Meeting(20824, 24805), Meeting(10195, 26912), Meeting(21831, 23857), Meeting(28116, 30517), Meeting(19430, 21315), Meeting(20357, 25868), Meeting(7730, 10834), Meeting(7208, 31979), Meeting(3303, 3382), Meeting(6868, 29637), Meeting(6979, 9924), Meeting(8197, 29568), Meeting(254, 3691), Meeting(21143, 26957), Meeting(508, 24213), Meeting(9433, 11128), Meeting(12781, 18086), Meeting(7120, 29809), Meeting(7011, 30975), Meeting(13793, 31234), Meeting(14111, 24641), Meeting(2236, 8377), Meeting(21386, 21488), Meeting(12361, 18900), Meeting(10805, 26256), Meeting(4695, 20456), Meeting(24610, 26732), Meeting(6553, 10176), Meeting(7353, 19260), Meeting(16707, 25620), Meeting(30721, 32263), Meeting(16831, 25518), Meeting(11089, 11783), Meeting(13106, 27962), Meeting(20029, 31443), Meeting(10048, 20319), Meeting(12734, 25554), Meeting(289, 22017), Meeting(15014, 26075), Meeting(4096, 10422), Meeting(2518, 21149), Meeting(10754, 27673), Meeting(14142, 29874), Meeting(16323, 17958), Meeting(5698, 25042), Meeting(24355, 26312), Meeting(24058, 30895), Meeting(7134, 13841), Meeting(6766, 32077), Meeting(19766, 20717), Meeting(13813, 23741), Meeting(5139, 30940), Meeting(13091, 22470), Meeting(6381, 8027), Meeting(15723, 18012), Meeting(823, 9046), Meeting(1333, 22306), Meeting(13841, 19657), Meeting(12417, 23004), Meeting(945, 27956), Meeting(3623, 16078), Meeting(11909, 26059), Meeting(19048, 25658), Meeting(6288, 19192), Meeting(3842, 8170), Meeting(6826, 17261), Meeting(4524, 22988), Meeting(3133, 12869), Meeting(19906, 21211), Meeting(16595, 32453), Meeting(762, 22148), Meeting(13591, 22589), Meeting(4826, 5318), Meeting(6473, 24550), Meeting(1407, 13449), Meeting(2633, 32690), Meeting(11813, 32163), Meeting(3604, 28962), Meeting(6961, 18161), Meeting(3483, 21069), Meeting(5848, 15171), Meeting(14865, 29416), Meeting(2370, 31824), Meeting(22557, 30441), Meeting(17602, 29464), Meeting(2671, 19792), Meeting(8296, 16748), Meeting(5320, 6642), Meeting(10264, 25960), Meeting(3840, 13001), Meeting(19871, 31614), Meeting(1004, 19695), Meeting(16814, 20494), Meeting(2886, 25094), Meeting(15132, 21054), Meeting(20259, 30108), Meeting(12087, 15680), Meeting(23753, 29358), Meeting(7986, 11261), Meeting(618, 30660), Meeting(2866, 24224), Meeting(9015, 16441), Meeting(8811, 29326), Meeting(21873, 28413), Meeting(14835, 23346), Meeting(2496, 5015), Meeting(4616, 27591), Meeting(6317, 9354), Meeting(20400, 25682), Meeting(23961, 24490), Meeting(5495, 28419), Meeting(9399, 25350), Meeting(19115, 22151), Meeting(13435, 19911), Meeting(7462, 16731), Meeting(11336, 18274), Meeting(15734, 19005), Meeting(6713, 8993), Meeting(12747, 29013), Meeting(4583, 28218), Meeting(6431, 25762), Meeting(974, 16573), Meeting(4778, 17314), Meeting(1291, 14770), Meeting(273, 32441), Meeting(19653, 30983), Meeting(9453, 11972), Meeting(12050, 26496), Meeting(23626, 28464), Meeting(828, 30414), Meeting(1458, 5124), Meeting(9737, 16670), Meeting(1377, 5454), Meeting(17526, 29623), Meeting(14499, 15314), Meeting(6732, 28983), Meeting(22046, 26723), Meeting(13123, 13521), Meeting(1110, 1135), Meeting(23954, 24461), Meeting(1803, 4921), Meeting(5157, 16751), Meeting(3086, 13092), Meeting(8776, 13477), Meeting(16102, 16282), Meeting(1556, 23915), Meeting(13086, 23521), Meeting(8993, 21815), Meeting(545, 25043), Meeting(16289, 24312), Meeting(2146, 8394), Meeting(12149, 22735), Meeting(7817, 26640), Meeting(22575, 22642), Meeting(16445, 17197), Meeting(8649, 30274), Meeting(10129, 14608), Meeting(2829, 10305), Meeting(1006, 16187), Meeting(14640, 27983), Meeting(4934, 29229), Meeting(9721, 15703), Meeting(13449, 21507), Meeting(21337, 28563), Meeting(1372, 22358), Meeting(13702, 32199), Meeting(17528, 21753), Meeting(9002, 27882), Meeting(1623, 14047) };
   auto        meetings3 = vector<Meeting>{Meeting(1, 12),Meeting(1,3),Meeting(5,7),Meeting(14,15),Meeting(4,8),Meeting(3,6),Meeting(13,14),Meeting(2, 9),Meeting(7, 14),Meeting(4, 6),Meeting(8, 8),Meeting(9899, 27000), Meeting(7394, 28322), Meeting(22300, 24431), Meeting(12385, 12859), Meeting(3659, 30534), Meeting(1274, 25378), Meeting(15264, 25022), Meeting(2570, 13069), Meeting(16879, 25465), Meeting(4215, 8218), Meeting(2831, 9095), Meeting(6467, 22802), Meeting(23378, 24959), Meeting(14062, 29281), Meeting(8029, 12477), Meeting(5575, 28570), Meeting(2557, 15149), Meeting(26106, 32452), Meeting(12651, 13337), Meeting(15147, 27028), Meeting(1577, 30949), Meeting(1291, 12594), Meeting(25177, 30930), Meeting(16237, 19963), Meeting(13164, 14818), Meeting(16867, 17214), Meeting(4439, 32707), Meeting(8537, 11383), Meeting(22468, 22574), Meeting(11449, 21250), Meeting(20720, 21799), Meeting(10018, 16831), Meeting(17489, 31466), Meeting(5303, 6554), Meeting(17446, 24184), Meeting(9256, 13527), Meeting(6041, 28424), Meeting(12710, 13435), Meeting(7070, 26693), Meeting(10681, 18762), Meeting(11058, 13475), Meeting(11926, 28109), Meeting(1714, 8226), Meeting(19631, 23699), Meeting(12782, 15316), Meeting(16181, 23056), Meeting(17910, 19745), Meeting(20108, 24569), Meeting(23770, 31403), Meeting(11275, 24290), Meeting(10972, 31530), Meeting(5052, 25938), Meeting(25519, 32714), Meeting(8826, 22017), Meeting(835, 6773), Meeting(18896, 23498), Meeting(10899, 18332), Meeting(1082, 4299), Meeting(1694, 32090), Meeting(26, 14913), Meeting(9386, 13509), Meeting(2209, 27130), Meeting(13016, 18036), Meeting(25132, 26575), Meeting(10244, 30517), Meeting(7297, 30912), Meeting(28384, 28943), Meeting(4655, 25710), Meeting(16864, 21223), Meeting(29161, 29712), Meeting(4038, 22290), Meeting(26055, 28437), Meeting(25943, 27699), Meeting(12512, 21720), Meeting(4838, 25037), Meeting(1301, 10677), Meeting(5402, 30992), Meeting(1263, 31615), Meeting(11751, 17661), Meeting(10953, 31787), Meeting(27172, 30051), Meeting(6559, 18016), Meeting(5836, 25020), Meeting(5779, 9414), Meeting(21059, 32632), Meeting(16966, 23814), Meeting(1275, 20601), Meeting(16210, 26918), Meeting(25413, 32722), Meeting(9847, 22197), Meeting(3720, 28334), Meeting(916, 10413), Meeting(27545, 29578), Meeting(3526, 8615), Meeting(26520, 27256), Meeting(11887, 31408), Meeting(13011, 26316), Meeting(5697, 24468), Meeting(8936, 11545), Meeting(4520, 5965), Meeting(42, 2396), Meeting(6691, 29442), Meeting(16966, 21878), Meeting(19626, 29558), Meeting(39, 17376), Meeting(3826, 29471), Meeting(5910, 17050), Meeting(25700, 27658), Meeting(2660, 19750), Meeting(207, 25467), Meeting(11825, 29391), Meeting(11338, 32740), Meeting(16089, 18393), Meeting(4868, 18033), Meeting(10107, 22286), Meeting(12938, 26262), Meeting(9105, 16325), Meeting(4994, 31919), Meeting(15269, 22587), Meeting(22589, 23364), Meeting(24005, 27587), Meeting(10456, 27199), Meeting(6593, 25746), Meeting(5203, 7344), Meeting(2063, 12928), Meeting(15362, 16305), Meeting(16144, 25300), Meeting(4577, 29166), Meeting(17149, 21744), Meeting(13143, 21046), Meeting(1923, 19663), Meeting(8454, 15493), Meeting(16715, 32016), Meeting(8753, 24307), Meeting(9250, 17391), Meeting(7942, 29513), Meeting(10721, 22248), Meeting(10667, 32066), Meeting(18639, 20094), Meeting(10929, 12541), Meeting(1135, 32499), Meeting(6724, 12309), Meeting(24302, 28670), Meeting(188, 31479), Meeting(4616, 25723), Meeting(5942, 21913), Meeting(2656, 20266), Meeting(16711, 32412), Meeting(19156, 26355), Meeting(1716, 10742), Meeting(5954, 21306), Meeting(854, 24800), Meeting(4683, 7347), Meeting(19359, 24742), Meeting(7750, 27273), Meeting(22997, 31819), Meeting(25976, 32698), Meeting(15267, 24906), Meeting(8806, 14305), Meeting(2343, 20068), Meeting(3296, 30403), Meeting(6472, 24736), Meeting(20365, 32469), Meeting(9687, 23555), Meeting(4057, 31983), Meeting(11446, 15041), Meeting(14052, 29296), Meeting(13362, 29879), Meeting(141, 20680), Meeting(12561, 22717), Meeting(5586, 22839), Meeting(959, 6730), Meeting(5638, 13611), Meeting(20482, 26651), Meeting(12707, 31876), Meeting(1120, 20133), Meeting(1779, 20873), Meeting(6198, 30549), Meeting(16408, 27378), Meeting(5438, 18403), Meeting(1767, 20393), Meeting(989, 25178), Meeting(7248, 20087), Meeting(5808, 16742), Meeting(14302, 25887), Meeting(3852, 3884), Meeting(801, 6922), Meeting(20292, 22997), Meeting(2440, 20229), Meeting(24283, 31167), Meeting(7210, 20624), Meeting(16794, 24632), Meeting(6620, 11363), Meeting(4544, 30375), Meeting(2874, 5240), Meeting(2562, 31076), Meeting(3975, 16070), Meeting(26059, 32721), Meeting(14393, 29902), Meeting(8357, 16586), Meeting(8985, 23567), Meeting(8094, 8340), Meeting(14295, 27278), Meeting(4330, 21525), Meeting(13021, 13722), Meeting(21823, 24021), Meeting(5586, 23136), Meeting(7213, 21365), Meeting(9434, 12611), Meeting(6980, 7144), Meeting(10245, 27781), Meeting(12973, 27565), Meeting(6717, 20723), Meeting(6203, 32284), Meeting(422, 9372), Meeting(11799, 32395), Meeting(12926, 27270), Meeting(2831, 13149), Meeting(6687, 9672), Meeting(20796, 26161), Meeting(17961, 18422), Meeting(11682, 18073), Meeting(22418, 29483), Meeting(926, 23687), Meeting(543, 18213), Meeting(28853, 30165), Meeting(1087, 9602), Meeting(24039, 29127), Meeting(3156, 20502), Meeting(18627, 22611), Meeting(6175, 11402), Meeting(2531, 3965), Meeting(3862, 17580), Meeting(24944, 32297), Meeting(5068, 24341), Meeting(12626, 19647), Meeting(7165, 30905), Meeting(5838, 10736), Meeting(4469, 13591), Meeting(17615, 19003), Meeting(10747, 28393), Meeting(26017, 29583), Meeting(1713, 12504), Meeting(21305, 24022), Meeting(7698, 27415), Meeting(4368, 5498), Meeting(3306, 8578), Meeting(6194, 26408), Meeting(2216, 12265), Meeting(10641, 14548), Meeting(6852, 21694), Meeting(6816, 29693), Meeting(5004, 27613), Meeting(20509, 25906), Meeting(1061, 25002), Meeting(13525, 23342), Meeting(8185, 22070), Meeting(23839, 27824), Meeting(4589, 15395), Meeting(4812, 16740), Meeting(18069, 18953), Meeting(19096, 29899), Meeting(6935, 9891), Meeting(299, 11539), Meeting(17150, 21926), Meeting(15249, 16882), Meeting(18673, 22794), Meeting(19266, 27517), Meeting(16018, 19160), Meeting(28271, 30766), Meeting(9363, 15907), Meeting(1267, 27084), Meeting(5272, 13756), Meeting(28300, 31883), Meeting(221, 13483), Meeting(6904, 10183), Meeting(8115, 10820), Meeting(182, 31643), Meeting(5670, 32415), Meeting(12535, 15558), Meeting(13790, 17225), Meeting(24496, 32754), Meeting(21059, 23609), Meeting(3015, 12385), Meeting(13574, 28901), Meeting(6312, 18607), Meeting(22103, 22810), Meeting(12317, 32464), Meeting(18153, 28570), Meeting(4058, 22494), Meeting(10489, 17702), Meeting(7451, 24915), Meeting(20873, 29407), Meeting(12585, 13531), Meeting(14327, 15813), Meeting(9673, 22461), Meeting(11537, 27196), Meeting(3896, 8249), Meeting(13958, 15023), Meeting(24932, 31524), Meeting(13211, 19580), Meeting(16180, 27386), Meeting(1961, 28295), Meeting(24539, 27747), Meeting(8944, 28923), Meeting(9540, 15645), Meeting(3400, 8894), Meeting(11859, 21144), Meeting(7763, 10443), Meeting(9501, 22543), Meeting(12541, 14802), Meeting(11173, 27046), Meeting(8165, 18527), Meeting(10289, 25456), Meeting(8344, 23999), Meeting(8372, 11483), Meeting(2943, 28580), Meeting(16473, 32121), Meeting(12545, 26657), Meeting(18604, 29110), Meeting(12918, 16711), Meeting(13906, 16242), Meeting(29065, 31204), Meeting(21181, 26923), Meeting(115, 20696), Meeting(20314, 27422), Meeting(18735, 26878), Meeting(7898, 17889), Meeting(7598, 31631), Meeting(3647, 31907), Meeting(9796, 31692), Meeting(23096, 25268), Meeting(20824, 24805), Meeting(10195, 26912), Meeting(21831, 23857), Meeting(28116, 30517), Meeting(19430, 21315), Meeting(20357, 25868), Meeting(7730, 10834), Meeting(7208, 31979), Meeting(3303, 3382), Meeting(6868, 29637), Meeting(6979, 9924), Meeting(8197, 29568), Meeting(254, 3691), Meeting(21143, 26957), Meeting(508, 24213), Meeting(9433, 11128), Meeting(12781, 18086), Meeting(7120, 29809), Meeting(7011, 30975), Meeting(13793, 31234), Meeting(14111, 24641), Meeting(2236, 8377), Meeting(21386, 21488), Meeting(12361, 18900), Meeting(10805, 26256), Meeting(4695, 20456), Meeting(24610, 26732), Meeting(6553, 10176), Meeting(7353, 19260), Meeting(16707, 25620), Meeting(30721, 32263), Meeting(16831, 25518), Meeting(11089, 11783), Meeting(13106, 27962), Meeting(20029, 31443), Meeting(10048, 20319), Meeting(12734, 25554), Meeting(289, 22017), Meeting(15014, 26075), Meeting(4096, 10422), Meeting(2518, 21149), Meeting(10754, 27673), Meeting(14142, 29874), Meeting(16323, 17958), Meeting(5698, 25042), Meeting(24355, 26312), Meeting(24058, 30895), Meeting(7134, 13841), Meeting(6766, 32077), Meeting(19766, 20717), Meeting(13813, 23741), Meeting(5139, 30940), Meeting(13091, 22470), Meeting(6381, 8027), Meeting(15723, 18012), Meeting(823, 9046), Meeting(1333, 22306), Meeting(13841, 19657), Meeting(12417, 23004), Meeting(945, 27956), Meeting(3623, 16078), Meeting(11909, 26059), Meeting(19048, 25658), Meeting(6288, 19192), Meeting(3842, 8170), Meeting(6826, 17261), Meeting(4524, 22988), Meeting(3133, 12869), Meeting(19906, 21211), Meeting(16595, 32453), Meeting(762, 22148), Meeting(13591, 22589), Meeting(4826, 5318), Meeting(6473, 24550), Meeting(1407, 13449), Meeting(2633, 32690), Meeting(11813, 32163), Meeting(3604, 28962), Meeting(6961, 18161), Meeting(3483, 21069), Meeting(5848, 15171), Meeting(14865, 29416), Meeting(2370, 31824), Meeting(22557, 30441), Meeting(17602, 29464), Meeting(2671, 19792), Meeting(8296, 16748), Meeting(5320, 6642), Meeting(10264, 25960), Meeting(3840, 13001), Meeting(19871, 31614), Meeting(1004, 19695), Meeting(16814, 20494), Meeting(2886, 25094), Meeting(15132, 21054), Meeting(20259, 30108), Meeting(12087, 15680), Meeting(23753, 29358), Meeting(7986, 11261), Meeting(618, 30660), Meeting(2866, 24224), Meeting(9015, 16441), Meeting(8811, 29326), Meeting(21873, 28413), Meeting(14835, 23346), Meeting(2496, 5015), Meeting(4616, 27591), Meeting(6317, 9354), Meeting(20400, 25682), Meeting(23961, 24490), Meeting(5495, 28419), Meeting(9399, 25350), Meeting(19115, 22151), Meeting(13435, 19911), Meeting(7462, 16731), Meeting(11336, 18274), Meeting(15734, 19005), Meeting(6713, 8993), Meeting(12747, 29013), Meeting(4583, 28218), Meeting(6431, 25762), Meeting(974, 16573), Meeting(4778, 17314), Meeting(1291, 14770), Meeting(273, 32441), Meeting(19653, 30983), Meeting(9453, 11972), Meeting(12050, 26496), Meeting(23626, 28464), Meeting(828, 30414), Meeting(1458, 5124), Meeting(9737, 16670), Meeting(1377, 5454), Meeting(17526, 29623), Meeting(14499, 15314), Meeting(6732, 28983), Meeting(22046, 26723), Meeting(13123, 13521), Meeting(1110, 1135), Meeting(23954, 24461), Meeting(1803, 4921), Meeting(5157, 16751), Meeting(3086, 13092), Meeting(8776, 13477), Meeting(16102, 16282), Meeting(1556, 23915), Meeting(13086, 23521), Meeting(8993, 21815), Meeting(545, 25043), Meeting(16289, 24312), Meeting(2146, 8394), Meeting(12149, 22735), Meeting(7817, 26640), Meeting(22575, 22642), Meeting(16445, 17197), Meeting(8649, 30274), Meeting(10129, 14608), Meeting(2829, 10305), Meeting(1006, 16187), Meeting(14640, 27983), Meeting(4934, 29229), Meeting(9721, 15703), Meeting(13449, 21507), Meeting(21337, 28563), Meeting(1372, 22358), Meeting(13702, 32199), Meeting(17528, 21753), Meeting(9002, 27882), Meeting(1623, 14047) };
    
    //auto  const meetings1 = vector<Meeting>{ Meeting(1, 2),Meeting(3,4),Meeting(2,6),Meeting(5,7),Meeting(8,10),Meeting(9,15),Meeting(18,21),Meeting(20,30) };
    //auto  const meetings2 = vector<Meeting>{ Meeting(1, 2),Meeting(3,4),Meeting(2,6),Meeting(5,7),Meeting(8,10),Meeting(9,15),Meeting(18,21),Meeting(20,30) };
    //auto        meetings3 = vector<Meeting>{ Meeting(1, 2),Meeting(3,4),Meeting(2,6),Meeting(5,7),Meeting(8,10),Meeting(9,15),Meeting(18,21),Meeting(20,30) };

    auto t2 = high_resolution_clock::now();
      auto aabb = mergeRangesV2(meetings2);
    auto t3 = high_resolution_clock::now();
    cout << duration_cast<nanoseconds>(t3 - t2).count() << " nanoseconds passed in mergeRangesV2 O(nlgn) CURSO\n";
    for_each(aabb.begin(), aabb.end(),
        [](Meeting item) {cout << item.getStartTime() << "," << item.getEndTime() << endl;});
 
    auto t0 = high_resolution_clock::now();
    auto aa = mergeRangesV1(meetings1);
    auto t1 = high_resolution_clock::now();
    cout << duration_cast<nanoseconds>(t1 - t0).count() << " nanoseconds passed in mergeRangesV1 O(n2) mio con ERASE\n";
    for_each(aa.begin(), aa.end(),
        [](Meeting item) {cout << item.getStartTime() << "," << item.getEndTime() << endl;});

    auto t4 = high_resolution_clock::now();
    mergeRangesV3(meetings3);
    auto t5 = high_resolution_clock::now();
    cout << duration_cast<nanoseconds>(t5 - t4).count() << " nanoseconds passed in mergeRangesV3 O(n2) mio IN-PLACE\n";
    for_each(meetings3.begin(), meetings3.end(),
        [](Meeting item) {cout << item.getStartTime() << "," << item.getEndTime() << endl;});

    auto t6 = high_resolution_clock::now();
    auto aacc = mergeRanges(meetings1);
    auto t7 = high_resolution_clock::now();
    cout << duration_cast<nanoseconds>(t7 - t6).count() << " nanoseconds passed in mergeRanges O(nlgn) mio\n";
    for_each(aacc.begin(), aacc.end(),
        [](Meeting item) {cout << item.getStartTime() << "," << item.getEndTime() << endl;});

    int wait;
    cin >> wait;
    return 0;
}

