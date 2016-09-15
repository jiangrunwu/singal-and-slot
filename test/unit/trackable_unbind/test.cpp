// Unit test code for Event::Connect

#include "test.hpp"
#include <iostream>

#include <subject.hpp>
#include <observer.hpp>

using namespace std;
using cppevent::Sender;

Test::Test()
    : testing::Test() {
}

Test::~Test() {

}

/*
 *
 */
TEST_F(Test, unbind_all1) {
  Subject s1;
  Subject s2;
  Observer o;

  s1.event1().connect(&o, &Observer::OnTest1IntegerParam);
  s2.event0().connect(&o, &Observer::OnTest0);

  o.UnbindAll();

  ASSERT_TRUE((s1.event1().count_connections() == 0) &&
      (s2.event0().count_connections() == 0) &&
      (o.CountBindings() == 0));
}

/*
 *
 */
TEST_F(Test, unbind_all2) {
  Subject s1;
  Subject s2;
  Observer o;

  s1.event1().connect(&o, &Observer::OnTest1IntegerParam);
  s2.event0().connect(&o, &Observer::OnTest0);

  o.UnbindAll(&Observer::OnTest1IntegerParam);

  ASSERT_TRUE((s1.event1().count_connections() == 0) &&
      (s2.event0().count_connections() == 1) &&
      (o.CountBindings() == 1));
}

TEST_F(Test, unbind_all3) {
  Subject s1;
  Subject s2;
  Observer o;

  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);

  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);

  o.UnbindAll(&Observer::OnTestUnbindAllAt5);

  ASSERT_TRUE((o.CountBindings() == 4) &&
      (s1.event0().count_connections() == 4) &&
      (s2.event0().count_connections() == 0));
}

TEST_F(Test, unbind_all4) {
  Subject s1;
  Subject s2;
  Observer o;

  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);

  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);

  o.UnbindAll();

  ASSERT_TRUE((o.CountBindings() == 0) &&
      (s1.event0().count_connections() == 0) &&
      (s2.event0().count_connections() == 0));
}

TEST_F(Test, unbind_once)
{
  Subject s;
  Observer o;

  s.event0().connect(&o, &Observer::OnTestUnbindOnceAt5);

  s.fire_event0();  // 1
  ASSERT_TRUE((s.event0().count_connections() == 1) && (o.CountBindings() == 1) && (o.test0_count() == 1));

  s.fire_event0();  // 2
  s.fire_event0();  // 3
  s.fire_event0();  // 4
  s.fire_event0();  // 5

  ASSERT_TRUE((s.event0().count_connections() == 0) && (o.CountBindings() == 0) && (o.test0_count() == 5));

  s.fire_event0();  // no connection

  ASSERT_TRUE((s.event0().count_connections() == 0) && (o.CountBindings() == 0) && (o.test0_count() == 5));
}

TEST_F(Test, unbind_all_in_callback1) {
  Subject s;
  Observer o;

  s.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s.event0().connect(&o, &Observer::OnTestUnbindAllAt5);

  for (int i = 0; i < 6; i++) {
    s.fire_event0();
  }

  ASSERT_TRUE(o.CountBindings() == 0);
}

TEST_F(Test, unbind_all_in_callback2) {
  Subject s1;
  Subject s2;
  Observer o;

  s1.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s1.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s1.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s1.event0().connect(&o, &Observer::OnTestUnbindAllAt5);

  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllAt5);

  for (int i = 0; i < 6; i++) {
    s1.fire_event0();
  }

  ASSERT_TRUE((o.CountBindings() == 5) &&
      (s1.event0().count_connections() == 0) &&
      (s2.event0().count_connections() == 5));
}

TEST_F(Test, unbind_all_method_in_callback) {
  Subject s1;
  Subject s2;
  Observer o;

  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);
  s1.event0().connect(&o, &Observer::OnTest0);

  s2.event0().connect(&o, &Observer::OnTestUnbindAllMethodAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllMethodAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllMethodAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllMethodAt5);
  s2.event0().connect(&o, &Observer::OnTestUnbindAllMethodAt5);

  for (int i = 0; i < 6; i++) {
    s2.fire_event0();
  }

  ASSERT_TRUE((o.CountBindings() == 4) &&
      (s1.event0().count_connections() == 4) &&
      (s2.event0().count_connections() == 0));
}