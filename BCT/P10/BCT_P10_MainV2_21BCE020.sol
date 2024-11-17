// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

/**
 * @title ElectionV2
 * @dev This contract adds voting functionality to the original Election contract.
 * The storage layout remains consistent with the original contract.
 */
contract ElectionV2 {
    struct Candidate {
        uint id;
        string name;
        uint voteCount;
    }

    struct Voter {
        bool voted;
        uint vote;
    }

    address public electionOfficial;
    mapping(uint => Candidate) public candidates;
    uint public candidatesCount;

    mapping(address => Voter) public voters;
    bool public electionEnded;

    modifier onlyOfficial() {
        require(msg.sender == electionOfficial, "Only election official can call this function.");
        _;
    }

    function initialize(address _electionOfficial) public {
        require(electionOfficial == address(0), "Already initialized");
        electionOfficial = _electionOfficial;
    }

    function addCandidate(string memory _name) public onlyOfficial {
        candidatesCount++;
        candidates[candidatesCount] = Candidate(candidatesCount, _name, 0);
    }

    function vote(uint _candidateId) public {
        require(!voters[msg.sender].voted, "You have already voted.");
        require(_candidateId > 0 && _candidateId <= candidatesCount, "Invalid candidate.");

        voters[msg.sender].voted = true;
        voters[msg.sender].vote = _candidateId;

        candidates[_candidateId].voteCount++;
    }

    function endElection() public onlyOfficial {
        electionEnded = true;
    }

    function getCandidate(uint _candidateId) public view returns (string memory name, uint voteCount) {
        require(_candidateId > 0 && _candidateId <= candidatesCount, "Candidate does not exist.");
        Candidate memory candidate = candidates[_candidateId];
        return (candidate.name, candidate.voteCount);
    }

    function getWinner() public view returns (string memory winnerName) {
        require(electionEnded, "Election has not ended yet.");
        uint winningVoteCount = 0;
        uint winnerId = 0;
        
        for (uint i = 1; i <= candidatesCount; i++) {
            if (candidates[i].voteCount > winningVoteCount) {
                winningVoteCount = candidates[i].voteCount;
                winnerId = i;
            }
        }

        return candidates[winnerId].name;
    }
}