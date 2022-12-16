#pragma once
#include <cstddef>
#include <memory>
#include "Snowflake.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeRebound.h"
#include "SnowflakeSine.h"

class SnowflakePool
{
public:
	SnowflakePool();

	void spawnParticle();
	//template<typename SNOWFLAKETYPE>
	//void destroy(std::unique_ptr<SNOWFLAKETYPE[]>& pool, size_t poolSize, size_t deleteIdx)
	//{
	//	size_t dernierIdxDuTableau = poolSize - 1;
	//	pool[deleteIdx] = pool[dernierIdxDuTableau];
	//	poolSize--;
	//}
	void destroySF(size_t deleteIdx);
	void destroySFNC(size_t deleteIdx);
	void destroySFR(size_t deleteIdx);
	void destroySFS(size_t deleteIdx);
	//template<typename SNOWFLAKETYPE>
	//SNOWFLAKETYPE& get(size_t idx) const
	//{
	//  //////// ATTEMPT 1
	//	if (typeid(SNOWFLAKETYPE).name() == Snowflake)
	//		return poolSF[idx];
	//	if (typeid(SNOWFLAKETYPE).name() == SnowflakeNoContact)
	//		return poolSFNC[idx];
	//	if (typeid(SNOWFLAKETYPE).name() == SnowflakeRebound)
	//		return poolSFR[idx];
	//	if (typeid(SNOWFLAKETYPE).name() == SnowflakeSine)
	//		return poolSFS[idx];
	//  //////// ATTEMP 2
	//	//if (type == 1)
	//	//	return poolSF[idx];
	//	//if (type == 2)
	//	//	return poolSFNC[idx];
	//	//if (type == 3)
	//	//	return poolSFR[idx];
	//	//if (type == 4)
	//	//	return poolSFS[idx];
	//}
	Snowflake& getSF(size_t idx) const;
	Snowflake& getSFNC(size_t idx) const;
	Snowflake& getSFR(size_t idx) const;
	Snowflake& getSFS(size_t idx) const;
	size_t getNbParticles() const;

	size_t nbSF = 0;
	size_t nbSFNC = 0;
	size_t nbSFR = 0;
	size_t nbSFS = 0;
private:
	std::unique_ptr<Snowflake[]> poolSF;
	std::unique_ptr<SnowflakeNoContact[]> poolSFNC;
	std::unique_ptr<SnowflakeRebound[]> poolSFR;
	std::unique_ptr<SnowflakeSine[]> poolSFS;
	size_t nbParticles;
};