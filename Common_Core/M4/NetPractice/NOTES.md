# NetPractice Cheat Sheet
Last Updated: 2 September 2026 (NetPractice version 1.9)

The examples given in the explained answers section in this cheat sheet may change in future versions, hence it is better to follow the rules & explanations provided along with the answers.

## Table of contents:
- Notes
  - [NetPractice specific rules](#rules)
  - [IP Class Ranges](#ip-class-ranges)
  - [Subnet Mask](#subnet-mask)
- [Explained Answers](#explained-answers)
  - [Level 6](#level-6)
  - [Level 7](#level-7)
  - [Level 8](#level-8)
  - [Level 9](#level-9)
  - [Level 10](#level-10)

## Rules:
- Switches: Connects devices with the same mask & IPs that are in the same block. (A blind connecting wire)
- Router Interfaces: Two interfaces on the same router should never be in the same subnet block.
- Router Gateway: A router gateway IP must be the IP of the directly connected next-hop router interface on the path to the destination.
- Host Route Gateway: Must be the same IP as the immediate interface before the router.
- Generic Routes: Always try default routes first (default or 0.0.0.0/0)

## IP Class Ranges
Source: [Wikipedia - IP Addresses](https://en.wikipedia.org/wiki/IP_address)

| Class # |       Public IP Range       |       Private IP Range        | Subnet Mask (CIDR)  |         No of Networks         |
|:-------:|:---------------------------:|:-----------------------------:|:-------------------:|:------------------------------:|
|    A    |  1.0.0.0 - 126.255.255.255  |   10.0.0.0 - 10.255.255.255   |   255.0.0.0 (/8)    |              126               |
|    B    | 128.0.0.0 - 191.255.255.255 |  172.16.0.0 - 172.31.255.255  |  255.255.0.0 (/16)  |           2,097,150            |
|    C    | 192.0.0.0 - 223.255.255.255 | 192.168.0.0 - 192.168.255.255 | 255.255.255.0 (/24) |           16,777,214           |
|    D    | 224.0.0.0 - 239.255.255.255 |              N/A              |         N/A         |          Multicasting          |
|    E    | 240.0.0.0 - 255.255.255.255 |              N/A              |         N/A         |     Research/Experimental      |

<details>
  <summary>
    <h2 style="display: inline" name="subnet-mask">Subnet Mask</h2>
    <p>Source: <a href="https://www.aelius.com/njh/subnet_sheet.html">Aelius Subnet sheet</a></p>
    <p>See also <a href="https://www.ietf.org/rfc/rfc1878.txt">RFC 1878</a>.</p>
    <table>
      <tr><th>CIDR</th><th>Addresses</th><th>Hosts</th><th>Netmask</th></tr>
      <tr align="center"><th>/31</th><td>2</td><td>2</td><td>255.255.255.254</td></tr>
      <tr align="center"><th>/30</th><td>4</td><td>2</td><td>255.255.255.252</td></tr>
      <tr align="center"><th>/29</th><td>8</td><td>6</td><td>255.255.255.248</td></tr>
      <tr align="center"><th>/28</th><td>16</td><td>14</td><td>255.255.255.240</td></tr>
      <tr align="center"><th>/27</th><td>32</td><td>30</td><td>255.255.255.224</td></tr>
      <tr align="center"><th>/26</th><td>64</td><td>62</td><td>255.255.255.192</td></tr>
      <tr align="center"><th>/25</th><td>128</td><td>126</td><td>255.255.255.128</td></tr>
      <tr align="center"><th>/24</th><td>256</td><td>254</td><td>255.255.255.0</td></tr>
      <tr align="center"><th>/23</th><td>512</td><td>510</td><td>255.255.254.0</td></tr>
      <tr align="center"><th>/22</th><td>1,024</td><td>1,022</td><td>255.255.252.0</td></tr>
      <tr align="center"><th>/21</th><td>2,048</td><td>2,046</td><td>255.255.248.0</td></tr>
      <tr align="center"><th>/20</th><td>4,096</td><td>4,094</td><td>255.255.240.0</td></tr>
      <tr align="center"><th>/19</th><td>8,192</td><td>8,190</td><td>255.255.224.0</td></tr>
      <tr align="center"><th>/18</th><td>16,384</td><td>16,382</td><td>255.255.192.0</td></tr>
      <tr align="center"><th>/17</th><td>32,768</td><td>32,766</td><td>255.255.128.0</td></tr>
      <tr align="center"><th>/16</th><td>65,536</td><td>65,534</td><td>255.255.0.0</td></tr>
      <tr align="center"><th>/8</th><td>16,777,216</td><td>16,777,214</td><td>255.0.0.0</td></tr>
    </table>
  </summary>

  For /24, first 3 octets must match. For /16, first 2 octets. For /8, first octet.
  The octets that are 0 in the table above can be anywhere from 0-255.
  ## How to check a match
  1. Find the block size from the mask (table above).
  2. Divide the relevant octet by block size, round down → that's the block start.
  3. Both IPs must fall in the same block.
  4. First IP in block = network address (unusable). Last IP in block = broadcast (unusable). Everything between = usable.
  5. The only exception to Step 4 is if the CIDR is /31, then each set of 2 ips serve as a point-to-point link.
  **Example:** mask `.224` (block 32), IPs `.1` and `.222`
  - `.1` → block `0–31`
  - `.222` → block `192–223`
  - Different blocks → mismatch. Fix by moving one IP into the other's block.
    <table>
      <tr valign="top">
        <td>
          <p><b>/25 - 2 Subnets - 126 Hosts/Subnet</b></p>
          <table>
            <tr><th>Network #</th><th>IP Range</th><th>Broadcast</th></tr>
            <tr><td>.0</td><td>.1-.126</td><td>.127</td></tr>
            <tr><td>.128</td><td>.129-.254</td><td>.255</td></tr>
          </table>
        </td>
        <td rowspan="5">
          <p><b>/30 - 64 Subnets - 2 Hosts/Subnet</b></p>
          <table>
            <tr><th>Network #</th><th>IP Range</th><th>Broadcast</th></tr>
            <tr><td>.0</td><td>.1-.2</td><td>.3</td></tr>
            <tr><td>.4</td><td>.5-.6</td><td>.7</td></tr>
            <tr><td>.8</td><td>.9-.10</td><td>.11</td></tr>
            <tr><td>.12</td><td>.13-.14</td><td>.15</td></tr>
            <tr><td>.16</td><td>.17-.18</td><td>.19</td></tr>
            <tr><td>.20</td><td>.21-.22</td><td>.23</td></tr>
            <tr><td>.24</td><td>.25-.26</td><td>.27</td></tr>
            <tr><td>.28</td><td>.29-.30</td><td>.31</td></tr>
            <tr><td>.32</td><td>.33-.34</td><td>.35</td></tr>
            <tr><td>.36</td><td>.37-.38</td><td>.39</td></tr>
            <tr><td>.40</td><td>.41-.42</td><td>.43</td></tr>
            <tr><td>.44</td><td>.45-.46</td><td>.47</td></tr>
            <tr><td>.48</td><td>.49-.50</td><td>.51</td></tr>
            <tr><td>.52</td><td>.53-.54</td><td>.55</td></tr>
            <tr><td>.56</td><td>.57-.58</td><td>.59</td></tr>
            <tr><td>.60</td><td>.61-.62</td><td>.63</td></tr>
            <tr><td>.64</td><td>.65-.66</td><td>.67</td></tr>
            <tr><td>.68</td><td>.69-.70</td><td>.71</td></tr>
            <tr><td>.72</td><td>.73-.74</td><td>.75</td></tr>
            <tr><td>.76</td><td>.77-.78</td><td>.79</td></tr>
            <tr><td>.80</td><td>.81-.82</td><td>.83</td></tr>
            <tr><td>.84</td><td>.85-.86</td><td>.87</td></tr>
            <tr><td>.88</td><td>.89-.90</td><td>.91</td></tr>
            <tr><td>.92</td><td>.93-.94</td><td>.95</td></tr>
            <tr><td>.96</td><td>.97-.98</td><td>.99</td></tr>
            <tr><td>.100</td><td>.101-.102</td><td>.103</td></tr>
            <tr><td>.104</td><td>.105-.106</td><td>.107</td></tr>
            <tr><td>.108</td><td>.109-.110</td><td>.111</td></tr>
            <tr><td>.112</td><td>.113-.114</td><td>.115</td></tr>
            <tr><td>.116</td><td>.117-.118</td><td>.119</td></tr>
            <tr><td>.120</td><td>.121-.122</td><td>.123</td></tr>
            <tr><td>.124</td><td>.125-.126</td><td>.127</td></tr>
            <tr><td>.128</td><td>.129-.130</td><td>.131</td></tr>
            <tr><td>.132</td><td>.133-.134</td><td>.135</td></tr>
            <tr><td>.136</td><td>.137-.138</td><td>.139</td></tr>
            <tr><td>.140</td><td>.141-.142</td><td>.143</td></tr>
            <tr><td>.144</td><td>.145-.146</td><td>.147</td></tr>
            <tr><td>.148</td><td>.149-.150</td><td>.151</td></tr>
            <tr><td>.152</td><td>.153-.154</td><td>.155</td></tr>
            <tr><td>.156</td><td>.157-.158</td><td>.159</td></tr>
            <tr><td>.160</td><td>.161-.162</td><td>.163</td></tr>
            <tr><td>.164</td><td>.165-.166</td><td>.167</td></tr>
            <tr><td>.168</td><td>.169-.170</td><td>.171</td></tr>
            <tr><td>.172</td><td>.173-.174</td><td>.175</td></tr>
            <tr><td>.176</td><td>.177-.178</td><td>.179</td></tr>
            <tr><td>.180</td><td>.181-.182</td><td>.183</td></tr>
            <tr><td>.184</td><td>.185-.186</td><td>.187</td></tr>
            <tr><td>.188</td><td>.189-.190</td><td>.191</td></tr>
            <tr><td>.192</td><td>.193-.194</td><td>.195</td></tr>
            <tr><td>.196</td><td>.197-.198</td><td>.199</td></tr>
            <tr><td>.200</td><td>.201-.202</td><td>.203</td></tr>
            <tr><td>.204</td><td>.205-.206</td><td>.207</td></tr>
            <tr><td>.208</td><td>.209-.210</td><td>.211</td></tr>
            <tr><td>.212</td><td>.213-.214</td><td>.215</td></tr>
            <tr><td>.216</td><td>.217-.218</td><td>.219</td></tr>
            <tr><td>.220</td><td>.221-.222</td><td>.223</td></tr>
            <tr><td>.224</td><td>.225-.226</td><td>.227</td></tr>
            <tr><td>.228</td><td>.229-.230</td><td>.231</td></tr>
            <tr><td>.232</td><td>.233-.234</td><td>.235</td></tr>
            <tr><td>.236</td><td>.237-.238</td><td>.239</td></tr>
            <tr><td>.240</td><td>.241-.242</td><td>.243</td></tr>
            <tr><td>.244</td><td>.245-.246</td><td>.247</td></tr>
            <tr><td>.248</td><td>.249-.250</td><td>.251</td></tr>
            <tr><td>.252</td><td>.253-.254</td><td>.255</td></tr>
          </table>
        </td>
      </tr>
      <tr>
        <td>
          <p><b>/26 - 4 Subnets - 62 Hosts/Subnet</b></p>
          <table>
            <tr><th>Network #</th><th>IP Range</th><th>Broadcast</th></tr>
            <tr><td>.0</td><td>.1-.62</td><td>.63</td></tr>
            <tr><td>.64</td><td>.65-.126</td><td>.127</td></tr>
            <tr><td>.128</td><td>.129-.190</td><td>.191</td></tr>
            <tr><td>.192</td><td>.193-.254</td><td>.255</td></tr>
          </table>
        </td>
      </tr>
      <tr>
        <td>
          <p><b>/27 - 8 Subnets - 30 Hosts/Subnet</b></p>
          <table>
            <tr><th>Network #</th><th>IP Range</th><th>Broadcast</th></tr>
            <tr><td>.0</td><td>.1-.30</td><td>.31</td></tr>
            <tr><td>.32</td><td>.33-.62</td><td>.63</td></tr>
            <tr><td>.64</td><td>.65-.94</td><td>.95</td></tr>
            <tr><td>.96</td><td>.97-.126</td><td>.127</td></tr>
            <tr><td>.128</td><td>.129-.158</td><td>.159</td></tr>
            <tr><td>.160</td><td>.161-.190</td><td>.191</td></tr>
            <tr><td>.192</td><td>.193-.222</td><td>.223</td></tr>
            <tr><td>.224</td><td>.225-.254</td><td>.255</td></tr>
          </table>
        </td>
      </tr>
      <tr>
        <td>
          <p><b>/28 - 16 Subnets - 14 Hosts/Subnet</b></p>
          <table>
            <tr><th>Network #</th><th>IP Range</th><th>Broadcast</th></tr>
            <tr><td>.0</td><td>.1-.14</td><td>.15</td></tr>
            <tr><td>.16</td><td>.17-.30</td><td>.31</td></tr>
            <tr><td>.32</td><td>.33-.46</td><td>.47</td></tr>
            <tr><td>.48</td><td>.49-.62</td><td>.63</td></tr>
            <tr><td>.64</td><td>.65-.78</td><td>.79</td></tr>
            <tr><td>.80</td><td>.81-.94</td><td>.95</td></tr>
            <tr><td>.96</td><td>.97-.110</td><td>.111</td></tr>
            <tr><td>.112</td><td>.113-.126</td><td>.127</td></tr>
            <tr><td>.128</td><td>.129-.142</td><td>.143</td></tr>
            <tr><td>.144</td><td>.145-.158</td><td>.159</td></tr>
            <tr><td>.160</td><td>.161-.174</td><td>.175</td></tr>
            <tr><td>.176</td><td>.177-.190</td><td>.191</td></tr>
            <tr><td>.192</td><td>.193-.206</td><td>.207</td></tr>
            <tr><td>.208</td><td>.209-.222</td><td>.223</td></tr>
            <tr><td>.224</td><td>.225-.238</td><td>.239</td></tr>
            <tr><td>.240</td><td>.241-.254</td><td>.255</td></tr>
          </table>
        </td>
      </tr>
      <tr>
        <td>
          <p><b>/29 - 32 Subnets - 6 Hosts/Subnet</b></p>
          <table>
            <tr><th>Network #</th><th>IP Range</th><th>Broadcast</th></tr>
            <tr><td>.0</td><td>.1-.6</td><td>.7</td></tr>
            <tr><td>.8</td><td>.9-.14</td><td>.15</td></tr>
            <tr><td>.16</td><td>.17-.22</td><td>.23</td></tr>
            <tr><td>.24</td><td>.25-.30</td><td>.31</td></tr>
            <tr><td>.32</td><td>.33-.38</td><td>.39</td></tr>
            <tr><td>.40</td><td>.41-.46</td><td>.47</td></tr>
            <tr><td>.48</td><td>.49-.54</td><td>.55</td></tr>
            <tr><td>.56</td><td>.57-.62</td><td>.63</td></tr>
            <tr><td>.64</td><td>.65-.70</td><td>.71</td></tr>
            <tr><td>.72</td><td>.73-.78</td><td>.79</td></tr>
            <tr><td>.80</td><td>.81-.86</td><td>.87</td></tr>
            <tr><td>.88</td><td>.89-.94</td><td>.95</td></tr>
            <tr><td>.96</td><td>.97-.102</td><td>.103</td></tr>
            <tr><td>.104</td><td>.105-.110</td><td>.111</td></tr>
            <tr><td>.112</td><td>.113-.118</td><td>.119</td></tr>
            <tr><td>.120</td><td>.121-.126</td><td>.127</td></tr>
            <tr><td>.128</td><td>.129-.134</td><td>.135</td></tr>
            <tr><td>.136</td><td>.137-.142</td><td>.143</td></tr>
            <tr><td>.144</td><td>.145-.150</td><td>.151</td></tr>
            <tr><td>.152</td><td>.153-.158</td><td>.159</td></tr>
            <tr><td>.160</td><td>.161-.166</td><td>.167</td></tr>
            <tr><td>.168</td><td>.169-.174</td><td>.175</td></tr>
            <tr><td>.176</td><td>.177-.182</td><td>.183</td></tr>
            <tr><td>.184</td><td>.185-.190</td><td>.191</td></tr>
            <tr><td>.192</td><td>.193-.198</td><td>.199</td></tr>
            <tr><td>.200</td><td>.201-.206</td><td>.207</td></tr>
            <tr><td>.208</td><td>.209-.214</td><td>.215</td></tr>
            <tr><td>.216</td><td>.217-.222</td><td>.223</td></tr>
            <tr><td>.224</td><td>.225-.230</td><td>.231</td></tr>
            <tr><td>.232</td><td>.233-.238</td><td>.239</td></tr>
            <tr><td>.240</td><td>.241-.246</td><td>.247</td></tr>
            <tr><td>.248</td><td>.249-.254</td><td>.255</td></tr>
          </table>
        </td>
      </tr>
    </table>
</details>

> [!NOTE]
> CIDR /31 is a special case where both IPs in the block are usable for point-to-point links.
> The network and broadcast addresses do not exist in this case.
> This special case is not implemented in NetPractice.
> 
> Formula for calculating the number of hosts per network: 2^(32 - CIDR) - 2.
> The first &amp; last IPs in each subnet are reserved for the network and broadcast addresses. (Not usable for hosts)

## Explained Answers
Alphabets used in IPs are used as placeholders to denote an unknown number as it is dynamically allocated by the subject.
The letter 'x' is reserved to denote a missing number in the IP address that has no significance, usually used in default IP examples.
Alphabets can only represent 1 integer from 0 to 255.
<hr/>

> [!NOTE]
> Interface R1 kept as default for simplicity.
<details>
  <summary>
    <h3 style="display: inline" name="level-6">Level 6: Basic Subnetting & Gateway Routing</h3>
  </summary>
  <table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Host A Gateway</b></td>
      <td>a.b.c.1</td>
      <td>a.b.c.254</td>
      <td>Same as interface R1 IP &amp; points outbound traffic to it.</td>
    </tr>
    <tr>
      <td><b>Router R Route</b></td>
      <td>10.0.0.0/8</td>
      <td>0.0.0.0/0</td>
      <td>Replaces the private route with a standard default route.</td>
    </tr>
    <tr>
      <td><b>Internet I Route</b></td>
      <td>a.b.c.0/31</td>
      <td>a.b.c.0/0</td>
      <td>Expands the IP matching for the internet routing table.</td>
    </tr>
  </table>
</details>
<hr/>

> [!NOTE]
> Change all interface masks to /30. (255.255.255.252)
<details>
  <summary>
    <h3 style="display: inline" name="level-7">Level 7: Subnetting & Point-to-Point Links</h3>
  </summary>
<table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Host A Gateway</b></td>
      <td>0.0.0.0</td>
      <td>a.198.14.1</td>
      <td>Answer is locked to R11 IP as that field is locked. Points outbound traffic to interface R11.</td>
      </tr>
    <tr>
      <td><b>Router R1 Gateway</b></td>
      <td>0.0.0.0</td>
      <td>a.198.14.253</td>
      <td>Same as interface R21 IP &amp; routes traffic forward to it.</td>
    </tr>
    <tr>
      <td><b>Router R21 IP</b></td>
      <td>a.198.14.149</td>
      <td>a.198.14.253</td>
      <td>The only other valid IP in the block containing interface R12 IP.</td>
    </tr>
    <tr>
      <td><b>Router R22 IP</b></td>
      <td>a.198.14.252</td>
      <td>a.198.14.5</td>
      <td>Shifts to a different block instead of the broadcast IP block of interface R21 & R12.</td>
    </tr>
    <tr>
      <td><b>Router R2 Gateway</b></td>
      <td>0.0.0.0</td>
      <td>a.198.14.254</td>
      <td>Same as interface R12 IP &amp; routes traffic forward to it.</td>
    </tr>
    <tr>
      <td><b>Interface C1 IP</b></td>
      <td>a.198.14.1</td>
      <td>a.198.14.6</td>
      <td>The only other valid IP in the block with interface R22 IP.</td>
    </tr>
    <tr>
      <td><b>Host C Gateway</b></td>
      <td>0.0.0.0</td>
      <td>a.198.14.5</td>
      <td>Same as interface R22 IP &amp; points outbound traffic to it.</td>
    </tr>
  </table>
</details>
<hr/>

> [!NOTE]
> The locked Internet I route restricts the usable IP range to the 1st subnet block of /26.
> Using /28 masks for all interfaces, the 4 smaller subnets blocks was made as a subset, hence losing 8 more IPs as usable IPs.
> In the examples, network D used the 1st subnet, network C used the 2nd subnet, and the P2P (interface R13 & R21) used the last subnet.
> The 3rd subnet block was left unused as it is not needed for this level. The usable IPs in the 3rd subnet block are a.b.c.[33 - 46].
<details>
  <summary>
    <h3 style="display: inline" name="level-8">Level 8: Advanced Routing & Public IP Subnetting</h3>
  </summary>
  <table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Interface R22 IP</b></td>
      <td>192.168.0.254</td>
      <td>a.b.c.1</td>
      <td>Uses the 1st subnet block. Valid IPs: a.b.c.[1 to .14].</td>
    </tr>
    <tr>
      <td><b>Interface C1 IP</b></td>
      <td>192.168.0.1</td>
      <td>a.b.c.2</td>
      <td>Replaces the invalid private IP. Uses the same valid IP range as interface R22.</td>
    </tr>
    <tr>
      <td><b>Host C Gateway</b></td>
      <td>10.0.0.254</td>
      <td>a.b.c.1</td>
      <td>Same as interface R22 IP &amp; points outbound traffic to it.</td>
    </tr>
    <tr>
      <td><b>Interface R23 IP</b></td>
      <td>7.8.9.10</td>
      <td>a.b.c.17</td>
      <td>Uses the 2nd subnet block. Valid IPs: a.b.c.[17 to .30].</td>
    </tr>
    <tr>
      <td><b>Interface D1 IP</b></td>
      <td>7.9.10.11</td>
      <td>a.b.c.18</td>
      <td>Uses the same valid IP range as interface R23.</td>
    </tr>
    <tr>
      <td><b>Host D Gateway</b></td>
      <td>9.9.9.9</td>
      <td>a.b.c.17</td>
      <td>Same as interface R23 IP &amp; points outbound traffic to it.</td>
    </tr>
    <tr>
      <td><b>Interface R13 IP</b></td>
      <td>10.0.0.1</td>
      <td>a.b.c.62</td>
      <td>Match the locked router R2 gateway.</td>
    </tr>
    <tr>
      <td><b>Interface R21 IP</b></td>
      <td>10.0.0.2</td>
      <td>a.b.c.61</td>
      <td>Uses the last subnet block. Valid IPs: a.b.c.[49 - .61].</td>
    </tr>
    <tr>
      <td><b>Router R2 Route</b></td>
      <td>10.0.0.0/8</td>
      <td>0.0.0.0/0</td>
      <td>Forwards all outgoing traffic to interface R13.</td>
    </tr>
    <tr>
      <td><b>Router R1 1st Route & Gateway</b></td>
      <td>Route: <code>192.168.0.0/30</code>, Gateway: <code>10.0.0.2</code></td>
      <td>Route: <code>a.b.c.0/26</code>, Gateway: <code>a.b.c.61</code></td>
      <td>Match route to internet I route &amp; match gateway to interface R21 IP.</td>
    </tr>
    <tr>
      <td><b>Internet I Gateway</b></td>
      <td>163.d.250.254</td>
      <td>163.d.250.12</td>
      <td>Match the locked interface R12 IP.</td>
    </tr>
  </table>
</details>
<hr/>

> [!NOTE]
> Using multiple disparate public routing blocks rather than a single summarized block allows for more flexibility,
> hence the lack of need to change the default masks provided. All private IPs must be converted to valid public IPs,
> otherwise the internet will drop the traffic. See here: [NetPractice specific rules](#rules)
<details>
  <summary>
    <h3 style="display: inline" name="level-9">Level 9: Comprehensive Subnetting &amp; Multi-Hop Routing</h3>
  </summary>
  <h4>Network A &amp; B (Host A &amp; B, interface A1, B1 &amp; R11)</h4>
  <p>Host A is left as default for simplicity.</p>
  <table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Interface R11 IP</b></td>
      <td>192.168.x.1</td>
      <td>a.198.b.1</td>
      <td>Matches the default value of host A gateway. Valid IPs: a.198.b.[1 - 126].</td>
    </tr>
    <tr>
      <td><b>Interface A1 IP</b></td>
      <td>192.168.x.2</td>
      <td>a.198.b.2</td>
      <td>Same mask as interface R11's locked mask. Same IP ranges as interface R11</td>
    </tr>
    <tr>
      <td><b>Interface B1 IP</b></td>
      <td>192.168.x.42</td>
      <td>a.198.b.42</td>
      <td>Same mask as interface R11's locked mask. Same IP ranges as interface R11.</td>
    </tr>
    <tr>
      <td><b>Host B</b></td>
      <td>Route: <code>8.8.8.8/16</code>, Gate: <code>x.199.x.1</code></td>
      <td>Route: <code>default</code>, Gate: <code>a.198.b.1</code></td>
      <td>Gateway same as interface R11 IP.</td>
    </tr>
  </table>
  <h4>Network C &amp; D (Host C &amp; D, interface C1, D1, R13, R22 &amp; R23)</h4>
  <table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Interface R22 IP</b></td>
      <td>10.0.0.254</td>
      <td>11.0.0.254</td>
      <td>Exits Class A's private IP range.</td>
    </tr>
    <tr>
      <td><b>Interface C1 IP</b></td>
      <td>10.0.0.1</td>
      <td>11.0.0.1</td>
      <td>Exits Class A's private IP range.</td>
    </tr>
    <tr>
      <td><b>Host C Gateway</b></td>
      <td>10.0.0.254</td>
      <td>11.0.0.254</td>
      <td>Same as R22 IP &amp; points outbound traffic to it.</td>
    </tr>
    <tr>
      <td><b>Interface R23 IP</b></td>
      <td>8.8.8.8</td>
      <td>c.d.e.f</td>
      <td>Matches the locked host D gateway.</td>
    </tr>
    <tr>
      <td><b>Interface D1 IP</b></td>
      <td>g.h.19.131</td>
      <td>c.d.e.[f±1]</td>
      <td>Easiest way is just to adjust f by 1 to fit into the subnet block since </td>
    </tr>
    <tr>
      <td><b>Host D Route</b></td>
      <td>10.0.0.0/8</td>
      <td>0.0.0.0/0</td>
      <td>Replaces the private IP route with a default route.</td>
    </tr>
  </table>
  <h4>Devices connecting all networks to the internet (Router R1 &amp; R2, internet I, interface R11, R12, R13, R21)</h4>
  <p>Interface R21 &amp; R13 mask, router R1 1st &amp; 3rd route is left as default for simplicity.</p>
  <table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Interface R13 IP</b></td>
      <td>i.j.17.254</td>
      <td>i.j.18.254</td>
      <td>Uses the only other valid IP since R21's mask is /30. Changing the mask is not needed.</td>
    </tr>
    <tr>
      <td><b>Router R2 Gateway</b></td>
      <td>i.j.16.254</td>
      <td>i.j.18.254</td>
      <td>Same as interface R13 IP &amp; points outgoing traffic to it.</td>
    </tr>
    <tr>
      <td><b>Router R1 2nd Route &amp; Gateway</b></td>
      <td>Route: <code>192.168.24.12/26</code>, Gate: <code>g.h.15.253</code></td>
      <td>Route: <code>0.0.0.0/0</code>, Gate: <code>g.h.18.253</code></td>
      <td>Matches route to network D's network address. Matches gateway to interface R21 IP.</td>
    </tr>
    <tr>
      <td><b>Internet I 2nd Route</b></td>
      <td>10.0.0.0/27</td>
      <td>11.0.0.0/27</td>
      <td>Matches route to network C's network address.</td>
    </tr>
  </table>
</details>
<hr/>

> [!NOTE]
> Network H1 & H2 is forced to use 1st subnet of the /25 block due to the locked R11 mask.
> Because of this, only a.b.c.[129 - 254] can be used for other IPs outside the aforementioned networks.
> Interface R13 & R21 are forced to use the last subnet of the /30 block due to the locked R21 mask.
> Network H4 is forced to use the 3rd subnet of the /26 block due to the locked H41 mask.
> Since network H3 has the least locked fields, the remaining valid IPs for it are a.b.c.[193 - 250].
> 
> The biggest subnet mask that can be used for network H3 is /27, which reduces the valid IPs to a.b.c.[193 - 222].
> It is highly recommended to use /27 for network H3 as it allows for the most flexibility,
> but other subnet masks can be used as long as they are inside the a.b.c.[193 - 250] range.
> The possible masks for network H3 has to have a subset of those IP ranges. (2nd last subnet of the /27,
> 2nd to 4th last subnet of the /28, 2nd to 8th last subnet of the /29, and 2nd to 16th last subnet of the /30.)
<details>
  <summary>
    <h3 style="display: inline" name="level-10">Level 10: Multi-router routing with mixed subnet masks</h3>
  </summary>
  <table>
    <tr><th>Component</th><th>Default</th><th>Correct</th><th>Explanation</th></tr>
    <tr>
      <td><b>Internet I Route</b></td>
      <td>a.b.c.0/31</td>
      <td>a.b.c.0/1</td>
      <td>Expands the mask so internet I can reach all hosts. Valid routes: a.b.c.0/[0-24] or [1 - 223].0.0.0/0.</td>
    </tr>
    <tr>
      <td><b>Interface H21</b></td>
      <td>IP: <code>192.168.42.42</code>, Mask: <code>255.255.0.0</code></td>
      <td>IP: <code>a.b.c.3</code>, Mask: <code>255.255.255.128</code></td>
      <td>Replaces the IP with a public IP. Valid IPs: a.b.c.[3 - 126].</td>
    </tr>
    <tr>
      <td><b>Interface H11 Mask</b></td>
      <td>255.255.255.0</td>
      <td>255.255.255.128</td>
      <td>Match the locked interface R11 mask.</td>
    </tr>
    <tr>
      <td><b>Router R1 1st Route</b></td>
      <td>10.0.0.0/8</td>
      <td>0.0.0.0/0</td>
      <td>Replaces the private route with a standard default route.</td>
    </tr>
    <tr>
      <td><b>Interface R13 mask</b></td>
      <td>255.255.255.0</td>
      <td>255.255.255.252</td>
      <td>Shrinks the mask to establish a point-to-point link with the locked interface R21.</td>
    </tr>
    <tr>
      <td><b>Interface R23</b></td>
      <td>IP: <code>8.8.8.8</code> Mask: <code>/18</code></td>
      <td>IP: <code>a.b.c.129</code><br/>Mask: <code>255.255.255.192</code></td>
      <td>Match the locked host H4 gateway.</td>
    </tr>
    <tr>
      <td><b>Interface R22</b></td>
      <td>IP: <code>10.0.0.254</code>, Mask: <code>255.255.255.0</code></td>
      <td>IP: <code>a.b.c.250</code>, Mask: <code>/27</code></td>
      <td>Replaces the private IP gateway with a public IP for host H3.</td>
    </tr>
    <tr>
      <td><b>Interface H31</b></td>
      <td>IP: <code>192.168.0.1</code>, Mask: <code>255.255.255.0</code></td>
      <td>IP: <code>a.b.c.193</code>, Mask: <code>/27</code></td>
      <td>Assigns host H3 a valid public IP alongside interface R22 within the <code>a.b.c.192/27</code> subnet.</td>
    </tr>
    <tr>
      <td><b>Host H3 Gateway</b></td>
      <td>10.0.0.254</td>
      <td>a.b.c.193</td>
      <td>Same as interface R22 IP &amp; points outbound traffic to it.</td>
    </tr>
  </table>
</details>