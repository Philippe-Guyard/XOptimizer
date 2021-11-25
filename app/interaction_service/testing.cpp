#include <interaction_service.h>

void test_download(XOptimizer::InteractionService& s) {
    s.download_and_parse_map("corse", "haute_corse");
}
