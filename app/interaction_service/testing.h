#ifndef TESTING_H
#define TESTING_H

#endif // TESTING_H

//#include "interaction_service.h"
#include "file_storage.h"
class Testing{
public:
    Testing(XOptimizer::InteractionService*);
    Testing(){};
	void test_download();
	void test_parse_orders();
	void test_search_csv();
    void test_filestorage();
	void run_all();
    XOptimizer::InteractionService* service;
	QString test_resources;
};


