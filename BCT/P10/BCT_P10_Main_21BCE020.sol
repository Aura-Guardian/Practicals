// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Election {
    struct Candidate {
        uint id;
        string name;
        uint voteCount;
    }

    address public electionOfficial;
    mapping(uint => Candidate) public candidates;
    uint public candidatesCount;

    function initialize(address _electionOfficial) public {
        require(electionOfficial == address(0), "Already initialized");
        electionOfficial = _electionOfficial;
    }

    function addCandidate(string memory _name) public {
        candidatesCount++;
        candidates[candidatesCount] = Candidate(candidatesCount, _name, 0);
    }

    function getCandidate(uint _candidateId) public view returns (string memory, uint) {
        Candidate memory candidate = candidates[_candidateId];
        return (candidate.name, candidate.voteCount);
    }
}