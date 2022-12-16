#include <iostream>
#include <memory>
#include "Constants.h"
#include "SnowflakePool.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
using namespace std;

SnowflakePool::SnowflakePool()
{
	////// V1 a V4
	//nbParticles = 5000;

	////// V5
	size_t startingParticles = MAX_SNOWFLAKES;
	cout << "StartingParticles : " << startingParticles << endl;

	poolSF = make_unique<Snowflake[]>(MAX_SNOWFLAKES);
	poolSFNC = make_unique<SnowflakeNoContact[]>(MAX_SNOWFLAKES);
	poolSFR = make_unique<SnowflakeRebound[]>(MAX_SNOWFLAKES);
	poolSFS = make_unique<SnowflakeSine[]>(MAX_SNOWFLAKES);

	//////// V1
	//for (size_t i = 0; i < MAX_SNOWFLAKES; i++)
	//{
	//	double posX = rand() / (double)RAND_MAX * SCREEN_WIDTH;
	//	double posY = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
	//	Snowflake snowflake(posX, posY);
	//	poolSF[i] = snowflake;
	//}

	//////// V2
	//for (size_t i = 0; i< MAX_SNOWFLAKES; i++)
	//{
	//	double posX = rand() / (double)RAND_MAX * SCREEN_WIDTH;
	//	double posY = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
	//	Snowflake snowflake(posX, posY);
	//	int rnd = rand();
	//	if (rnd < RAND_MAX / 10)
	//		snowflake = SnowflakeRebound(posX, posY);
	//	else if (rnd < RAND_MAX / 5 * 2)
	//		snowflake = SnowflakeNoContact(posX, posY);
	//	else if (rnd < RAND_MAX / 2)
	//		snowflake = SnowflakeSine(posX, posY);
	//	else
	//		snowflake = Snowflake(posX, posY);
	//	poolSF[i] = snowflake;
	//}

	//////// V3
	//for (size_t i = 0; i < nbParticles; i++)
	//{
	//	/////// TEMPLATE
	//	//int rnd = rand();
	//	//if (rnd < RAND_MAX / 10)
	//	//{
	//	//	SnowflakeRebound sfR = createSF<SnowflakeRebound>();
	//	//	poolSFR[nbSFR] = sfR;
	//	//	nbSFR = nbSFR + 1;
	//	//}
	//	//else if (rnd < RAND_MAX / 5 * 2)
	//	//{
	//	//	SnowflakeNoContact sfNC = createSF<SnowflakeNoContact>();
	//	//	poolSFNC[nbSFNC] = sfNC;
	//	//	nbSFNC = nbSFNC + 1;
	//	//}
	//	//else if (rnd < RAND_MAX / 2)
	//	//{
	//	//	SnowflakeSine sfS = createSF<SnowflakeSine>();
	//	//	poolSFS[nbSFS] = sfS;
	//	//	nbSFS = nbSFS + 1;
	//	//}
	//	//else
	//	//{
	//	//	Snowflake sf = createSF<Snowflake>();
	//	//	poolSF[nbSF] = sf;
	//	//	nbSF = nbSF + 1;
	//	//}
	//	//////// TEMPLATES
	//	int rnd = rand();
	//	if (rnd < RAND_MAX / 10)
	//	{
	//		poolSFR[nbSFR] = SnowflakeRebound();
	//		nbSFR++;
	//	}
	//	else if (rnd < RAND_MAX / 5 * 2)
	//	{
	//		poolSFNC[nbSFNC] = SnowflakeNoContact();
	//		nbSFNC++;
	//	}
	//	else if (rnd < RAND_MAX / 2)
	//	{
	//		poolSFS[nbSFS] = SnowflakeSine();
	//		nbSFS++;
	//	}
	//	else
	//	{
	//		poolSF[nbSF] = Snowflake();
	//		nbSF++;
	//	}
	//}

	//////// V5
	for (size_t i = 0; i < MAX_SNOWFLAKES; i++)
	{
		poolSFR[i] = SnowflakeRebound();
		poolSFNC[i] = SnowflakeNoContact();
		poolSFS[i] = SnowflakeSine();
		poolSF[i] = Snowflake();
	}

	for (size_t i = 0; i < startingParticles; i++)
	{
		int rnd = rand();
		if (rnd < RAND_MAX / 10)
			nbSFR++;
		else if (rnd < RAND_MAX / 5 * 2)
			nbSFNC++;
		else if (rnd < RAND_MAX / 2)
			nbSFS++;
		else
			nbSF++;
	}

	//////// V5
	//for (int i = 0; i < startingParticles; i++)
	//	spawnParticle();
}

void SnowflakePool::spawnParticle()
{
	if (nbParticles < MAX_SNOWFLAKES)
	{
		int rnd = rand();
		if (rnd < RAND_MAX / 10)
		{
			poolSFR[nbSFR].init();
			nbSFR++;
		}
		else if (rnd < RAND_MAX / 5 * 2)
		{
			poolSFNC[nbSFNC].init();
			nbSFNC++;
		}
		else if (rnd < RAND_MAX / 2)
		{
			poolSFS[nbSFS].init();
			nbSFS++;
		}
		else
		{
			poolSF[nbSF].init();
			nbSF++;
		}
	}
}

void SnowflakePool::destroySF(size_t deleteIdx)
{
	size_t dernierIdxDuTableau = nbSF - 1;
	poolSF[deleteIdx] = poolSF[dernierIdxDuTableau];
	nbSF--;
}
void SnowflakePool::destroySFNC(size_t deleteIdx)
{
	size_t dernierIdxDuTableau = nbSFNC - 1;
	poolSFNC[deleteIdx] = poolSFNC[dernierIdxDuTableau];
	nbSFNC--;
}
void SnowflakePool::destroySFR(size_t deleteIdx)
{
	size_t dernierIdxDuTableau = nbSFR - 1;
	poolSFR[deleteIdx] = poolSFR[dernierIdxDuTableau];
	nbSFR--;
}
void SnowflakePool::destroySFS(size_t deleteIdx)
{
	size_t dernierIdxDuTableau = nbSFS - 1;
	poolSFS[deleteIdx] = poolSFS[dernierIdxDuTableau];
	nbSFS--;
}

Snowflake& SnowflakePool::getSF(size_t idx) const
{
	return poolSF[idx];
}
Snowflake& SnowflakePool::getSFNC(size_t idx) const
{
	return poolSFNC[idx];
}
Snowflake& SnowflakePool::getSFR(size_t idx) const
{
	return poolSFR[idx];
}
Snowflake& SnowflakePool::getSFS(size_t idx) const
{
	return poolSFS[idx];
}

size_t SnowflakePool::getNbParticles() const
{
	return (nbSF+nbSFNC+nbSFR+nbSFS);
}
