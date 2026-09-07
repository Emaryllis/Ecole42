_This project has been created as part of the 42 curriculum by egoh._
# Netpractice
A practical networking project designed to build a deep, foundational understanding of network architecture, addressing, routing, and subnetting.
## Description
A system administration project focused on configuring small-scale network topologies. The goal of the project is to solve a series of 10 increasingly complex network configurations, addressing connectivity issues by calculating IP addresses, defining appropriate subnet masks, and setting up routing rules.
Through an interactive training interface, this project bridges theoretical networking concepts with practical application, ensuring a solid grasp of how data moves across Local Area Networks (LANs) and interconnected subnets.
## Instructions
### Running the Training Interface
The project comes with a local web interface that serves as the training and testing environment.
1. Clone the repository
2. Enter the repository folder
3. Run the project using the given `./run.sh`
4. A browser window should automatically open with the project directly in view
### Exporting Configurations & Submission Requirements
To validate and submit work, each level must be solved in its entirety.
- Solve each level according to the requirements with the help of the logs at the bottom right corner.
- Click the export button to download the level answers into a JSON file
- Move the file into the root of the repository
- Submit the project when all 10 configuration files are present
#### Expected Repository Root Structure:
```
netpractice/
├── level-1
├── level-2
├── level-3
├── level-4
├── level-5
├── level-6
├── level-7
├── level-8
├── level-9
├── level-10
└── README.md
```
> [!NOTE]
> Do not place configuration files in subfolders. All 10 files must reside strictly at the repository root for automated evaluation.
## Resources
### Networking Concepts Covered
* TCP/IP addressing:
    * Private vs. public IP ranges
    * network & host IDs
    * Broadcast addresses
* Subnet Masks:
    * Subnet Masks & CIDR notation
    * Calculating host capacity
    * Understanding binary subnet boundaries
    * Working with slash notation
* Default gateways:
    * Routes for outbound network traffic leaving local segments
* Routers:
    * Static routing
    * Next-hop logic
    * Inter-vlan/Inter-subnet communication
* Routers versus Switches:
    * Understanding Layer 2 broadcasting (switching) versus Layer 3 packet forwarding (routing)
* OSI Model
    * Focusing primarily on Layer 2 (Data Link) and Layer 3 (Network).
### LLM Usage
* Used for clarification on CIDR notation
* Verifier for submitted answers
* Alternate permutations of answers that also work that includes explanation for better understanding
### References & Documentation
* [RFC 1918 - Address Allocation for Private Internets](https://datatracker.ietf.org/doc/html/rfc1918)
