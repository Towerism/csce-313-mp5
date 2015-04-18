#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>
#include "histo_world.h"
#include "histo_client.h"
#include "bounded_buffer.h"
#include "ascii-engine/include/ascii-engine/engine.h"

TEST(HistogramTest, Generate) {
  ascii_engine::Engine engine(60);
  HistoWorld * h = new HistoWorld(200, 100);
  Bounded_buffer<int> buf(3);
  h->addClient(new HistoClient("Joe", buf));
  h->addClient(new HistoClient("Joe", buf));
  h->addClient(new HistoClient("Joe", buf));
  engine.set_world(std::shared_ptr<ae::World>(h));
  engine.game_loop();
}

TEST(HistogramTest, Add) {
  ascii_engine::Engine engine(60);
  HistoWorld * h = new HistoWorld(200, 100);
  Bounded_buffer<int> buf(3);
  HistoClient * hc_1 = new HistoClient("Joe Smith", buf);
  HistoClient * hc_2 = new HistoClient("Jane Smith", buf);
  HistoClient * hc_3 = new HistoClient("John Doe", buf);
  HistoClient * hc_4 = new HistoClient("John Doe", buf);
  hc_1->addData(1);
  hc_1->addData(1);
  hc_1->addData(1);
  hc_1->addData(40);
  hc_1->addData(1);
  hc_1->addData(1);
  hc_1->addData(1);
  hc_1->addData(1);
  hc_2->addData(49);
  hc_2->addData(49);
  hc_2->addData(49);
  hc_2->addData(40);
  hc_2->addData(40);
  hc_2->addData(40);
  hc_2->addData(40);
  engine.set_world(std::shared_ptr<ae::World>(h));
  h->addClient(hc_1);
  h->addClient(hc_2);
  h->addClient(hc_3);
  h->addClient(hc_4);
  engine.game_loop();
}
