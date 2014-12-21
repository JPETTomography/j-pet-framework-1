#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetEvent/JPetEvent.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetEvent event;
  BOOST_REQUIRE_EQUAL(event.getTime(), 0.0f);
  BOOST_REQUIRE_EQUAL(event.getQualityOfTime(), 0.0f);
  
  //BOOST_REQUIRE(event.fHits->first == NULL);
  //BOOST_REQUIRE(event.fHits->second == NULL);
}

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetHit firstHit;
  JPetHit secondHit;
  JPetEvent event(8.5f, 4.5f, firstHit, secondHit);
  
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getTime(), 8.5f, epsilon);
  BOOST_REQUIRE_CLOSE(event.getQualityOfTime(), 4.5f, epsilon);
  
  BOOST_REQUIRE_CLOSE(event.getTimeDiff(), 0.f, epsilon);
  
  BOOST_REQUIRE_EQUAL(event.fTimeDiff, 0.f);
  BOOST_REQUIRE_EQUAL(event.fQualityOfTimeDiff, 0.f);
  BOOST_REQUIRE_EQUAL(event.fNhits, 2.f);
}

BOOST_AUTO_TEST_CASE(hitTest)
{
  JPetHit firstHit;
  JPetHit secondHit;
  JPetEvent event(8.5f, 4.5f, firstHit, secondHit);
  
  BOOST_REQUIRE(event.getFirstHit().getEnergy() == firstHit.getEnergy());
  BOOST_REQUIRE(event.getSecondHit().getEnergy() == firstHit.getEnergy());
  
  BOOST_REQUIRE(event[1].getEnergy() == firstHit.getEnergy());
  //BOOST_REQUIRE(event[2].getEnergy() == secondHit.getEnergy()); // BUG JPetEvent::operator[](int i)

  JPetHit fh;
  JPetHit sh;  
  fh.setScinID(8);
  sh.setScinID(16);
  event.setHits(fh, sh);
  BOOST_REQUIRE(event.getFirstHit().getScinID() == fh.getScinID());
  BOOST_REQUIRE(event.getSecondHit().getScinID() == sh.getScinID());
  
  fh.setScinID(32);
  sh.setScinID(64);
  event.setFirstHit(fh);
  event.setSecondHit(sh);
  BOOST_REQUIRE(event.getFirstHit().getScinID() == fh.getScinID());
  BOOST_REQUIRE(event.getSecondHit().getScinID() == sh.getScinID());  
}

BOOST_AUTO_TEST_CASE(timeDiffTest)
{
  JPetEvent event;
  event.setTimeDiff(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getTimeDiff(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(qualityOfTimeTest)
{
  JPetEvent event;
  event.setQualityOfTimeDiff(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.fQualityOfTime, 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(timeTest)
{
  JPetEvent event;
  event.setTime(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getTime(), 111.f, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
