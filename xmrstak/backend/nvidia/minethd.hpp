#pragma once

#include "xmrstak/jconf.hpp"
#include "jconf.hpp"
#include "nvcc_code/cryptonight.hpp"

#include "xmrstak/backend/cpu/crypto/cryptonight.h"
#include "xmrstak/backend/iBackend.hpp"
#include "xmrstak/misc/environment.hpp"

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>


namespace xmrstak
{
namespace nvidia
{

class minethd : public iBackend
{
public:

	static void switch_work(miner_work& pWork);
	static std::vector<iBackend*>* thread_starter(uint32_t threadOffset, miner_work& pWork);
	static bool self_test();

private:
	typedef void (*cn_hash_fun)(const void*, size_t, void*, cryptonight_ctx*);
	
	minethd(miner_work& pWork, size_t iNo, const jconf::thd_cfg& cfg);

	void work_main();
	void consume_work();

	static std::atomic<uint64_t> iGlobalJobNo;
	static std::atomic<uint64_t> iConsumeCnt;
	static uint64_t iThreadCount;
	uint64_t iJobNo;

	static miner_work oGlobalWork;
	miner_work oWork;

	std::thread oWorkThd;

	nvid_ctx ctx;

	bool bQuit;
};

} // namespace nvidia
} // namepsace xmrstak
