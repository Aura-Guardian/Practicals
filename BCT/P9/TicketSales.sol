// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract TicketSales {
    address public organizer;
    uint256 public eventCount;

    struct Event {
        uint256 id;
        string name;
        uint256 date;
        uint256 price;
        uint256 totalTickets;
        uint256 ticketsSold;
        bool isActive;
    }

    mapping(uint256 => Event) public events;
    mapping(uint256 => mapping(address => uint256)) public ticketsOwned;

    event EventCreated(uint256 id, string name, uint256 date, uint256 price, uint256 totalTickets);
    event TicketPurchased(uint256 eventId, address buyer, uint256 amount);
    event TicketRefunded(uint256 eventId, address buyer, uint256 amount);

    constructor() {
        organizer = msg.sender;
    }

    modifier onlyOrganizer() {
        require(msg.sender == organizer, "Only organizer allowed");
        _;
    }

    modifier eventExists(uint256 eventId) {
        require(events[eventId].id == eventId, "Event does not exist");
        _;
    }

    function createEvent(string memory name, uint256 date, uint256 price, uint256 totalTickets) public onlyOrganizer {
        require(date > block.timestamp && totalTickets > 0, "Invalid event details");

        eventCount++;
        events[eventCount] = Event(eventCount, name, date, price, totalTickets, 0, true);

        emit EventCreated(eventCount, name, date, price, totalTickets);
    }

    function buyTickets(uint256 eventId, uint256 quantity) public payable eventExists(eventId) {
        Event storage _event = events[eventId];
        require(_event.isActive && block.timestamp < _event.date, "Event not active or past");
        require(quantity > 0 && _event.ticketsSold + quantity <= _event.totalTickets, "Invalid ticket quantity");
        require(msg.value == quantity * _event.price, "Incorrect payment");

        _event.ticketsSold += quantity;
        ticketsOwned[eventId][msg.sender] += quantity;

        emit TicketPurchased(eventId, msg.sender, quantity);
    }

    function availableTickets(uint256 eventId) public view eventExists(eventId) returns (uint256) {
        return events[eventId].totalTickets - events[eventId].ticketsSold;
    }

    function deactivateEvent(uint256 eventId) public onlyOrganizer eventExists(eventId) {
        events[eventId].isActive = false;
    }

    function withdrawFunds() public onlyOrganizer {
        payable(organizer).transfer(address(this).balance);
    }

    function refundTickets(uint256 eventId, uint256 quantity) public eventExists(eventId) {
        require(ticketsOwned[eventId][msg.sender] >= quantity, "Insufficient tickets to refund");
        
        Event storage _event = events[eventId];
        uint256 refundAmount = quantity * _event.price;
        _event.ticketsSold -= quantity;
        ticketsOwned[eventId][msg.sender] -= quantity;
        
        payable(msg.sender).transfer(refundAmount);
        emit TicketRefunded(eventId, msg.sender, quantity);
    }

    function ticketsOwnedByUser(uint256 eventId, address user) public view eventExists(eventId) returns (uint256) {
        return ticketsOwned[eventId][user];
    }
}
