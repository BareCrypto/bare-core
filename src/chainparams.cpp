// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Phore developers
// Copyright (c) 2018-2019 The Monetaryunit developers
// Copyright (c) 2019 The Bare developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "bignum.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */
static bool regenerate = false;

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (     0, uint256("000000731191b78b71c7352a3f877e9429d5b26b67c41020e21dffb14f783b50"))
	(   515, uint256("899bc6a7c9c674adaca31defd5c58993564bd7ca4aae61438c4afa782afdd38b"))
	( 23993, uint256("e82e40035a0a71d3065929f47dcc90c16bf9af9e2b731b4ef1eb37ee4437c3a5"))
	( 50005, uint256("4ca265ce1bceeae7a08606db0fdb83b0cb0ef603a25f64a1b8754dc488f18207"))
    ( 97996, uint256("c851870c5f3139f4700b6a1ab22051580ecb9b7f7727829d7209bffb54001ee5"))
    (104792, uint256("d712a06d3f0272dc0dc39e46df4b9755b6c97a41ce92b1901b2417e08774571f"))
    (126806, uint256("2d3e4fe9ceab771ed49a708bb209f1695de10a5af10b652adb2e991fe52e2543"))
    (160175, uint256("6559c13bc449f1a68302a77945936ca3842c0bcbb9573a9e37cff687359fcb93"));
    

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1569358051, // * UNIX timestamp of last checkpoint block
    322445,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2900        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("00000bbf8583c8e4a300436924e68e6dc4cd143881c852dac407fbc33d1158b3"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1505224800,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000d5cf5963fdf58a973c59fdb37f830a5b0118ac91b8ef0741ad2fdff3d99"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1505224800,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x6E;
        pchMessageStart[1] = 0x71;
        pchMessageStart[2] = 0x74;
        pchMessageStart[3] = 0x59;
        vAlertPubKey = ParseHex("0432646f6ccc79c8db3c567c625f3293fbffa077c702035d77f2fcd2620f90fc77f28b98f463ac81b7ab6a5dfe17ea9da3a137833eea7a596f3c3a4ef6850adbbe");
        nDefaultPort = 27003;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bare: 1 minute
        nTargetSpacing = 1 * 60;  // Bare: 60 seconds
        nMaturity = 24;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 4000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 500;
        nModifierUpdateBlock = 1;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Bare is crypto for adults - 31/May/2019.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1559634300;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 243603;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            LogPrintf("Mainnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("000000731191b78b71c7352a3f877e9429d5b26b67c41020e21dffb14f783b50"));
            assert(genesis.hashMerkleRoot == uint256("023b3b4bd3fb83cd05066b9d8104ebc5ba76f81ee9743533490e9dffa36a4379"));
        }
        // Mainnet --- nonce: 1 time: 1536266133 hash: 0x0b58ed450b3819ca54ab0054c4d220ca4f887d21c9e55d2a333173adf76d987f merklehash: 0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e

        vSeeds.push_back(CDNSSeedData("dns1", "dns1.bare.network"));
        vSeeds.push_back(CDNSSeedData("dns2", "dns2.bare.network"));
		vSeeds.push_back(CDNSSeedData("dns3", "dns3.bare.network"));
        vSeeds.push_back(CDNSSeedData("dns4", "dns4.bare.network"));
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25); //Bare adresses start with "B"
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 110);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0xbd).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "ba";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04a8e3030242c007ca14373355bb62733aa635d3cda8225817750b1deee91751222870c860ba3bca6cb9583806f36617f0d248e01673a0f4ffea0722cb82a584a0";
        strSporkKeyTemp = "04a8e3030242c007ca14373355bb62733aa635d3cda8225817750b1deee91751222870c860ba3bca6cb9583806f36617f0d248e01673a0f4ffea0722cb82a584a0";
        strObfuscationPoolDummyAddress = "B5pmqYrEUrqknhFZRajHrbudBx1DDkLbBE";
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xff;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0x44;
        vAlertPubKey = ParseHex("04e4131cace7dce061a374cbc50b5a5cb1133a97b0afe454dc65944d7bf469f6709723911e0cde507014734be1efa1234e59231084238f75d27c771a69a46a31a1");
        nDefaultPort = 23660;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bare: 1 day
        nTargetSpacing = 1 * 10;  // Bare: 1 minute
        nMaturity = 2;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000000 * COIN;
        nLastPOWBlock = 2000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1559634301;
        genesis.nNonce = 274266;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x7fbf5849b7a8602fecd2d5e4465b3d4f0bfb482b02c87388b925009d14ba7e42"));
            assert(genesis.hashMerkleRoot == uint256("0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e"));
        }
        // Testnet --- nonce: 1 time: 1505224800 hash: 0x7fbf5849b7a8602fecd2d5e4465b3d4f0bfb482b02c87388b925009d14ba7e42 merklehash: 0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("testnetdns", "testnetdns.bare.org"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet bare addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet bare script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 196);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet bare BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet bare BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet bare BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tb";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKeyTemp = "0460f73eaa521369fa2c9b02b9fae90ab45d0eea30d8cb642916f5b8826606e4d6b26f5e0a74cdd357b556af0d756310701f1111c5977c67f3e34e1d7c4b8381fc";
        strSporkKey = "0460f73eaa521369fa2c9b02b9fae90ab45d0eea30d8cb642916f5b8826606e4d6b26f5e0a74cdd357b556af0d756310701f1111c5977c67f3e34e1d7c4b8381fc";
        strObfuscationPoolDummyAddress = "BA3M1g3WNqhXkSmuG31Z3DTQqEVEbdTWEE";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x54;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x64;
        pchMessageStart[3] = 0x95;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Bare: 1 day
        nTargetSpacing = 1 * 60;        // Bare: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1559634302;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1392095;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nDefaultPort = 19685;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtestnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Regtestnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x613e35c5b607586d3f5b8b109d162eac5fca0be0b0fa282277092e8dea8af138"));
            assert(genesis.hashMerkleRoot == uint256("0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e"));
        }
        // Regtestnet --- nonce: 12347 time: 1505224800 hash: 0x613e35c5b607586d3f5b8b109d162eac5fca0be0b0fa282277092e8dea8af138 merklehash: 0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e

        if (regenerate)
            exit(0);

        bech32_hrp = "murt";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // {
        //     "PrivateKey": "923EhWh2bJHynX6d4Tqt2Q75bhTDCT1b4kff3qzDKDZHZ6pkQs7",
        //     "PublicKey": "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a"
        // }
        strSporkKey = "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a";
        strSporkKeyTemp = "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 27005;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
