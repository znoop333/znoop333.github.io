<html><head>
<title>Dave's Image Processing Website</title>
<link rel="stylesheet" type="text/css" media="all" href="papers.css">
<link rel="stylesheet" type="text/css" media="screen" href="papers-screen.css">
<link rel="stylesheet" type="text/css" media="print" href="papers-print.css">
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
</head>

<style type="text/css">

</style>

<body >

<div id="outerContainer">

<!-- Site Navigation Menu -->
<div id="MyMenu">
<ul>
<li class="MyMenuItem"><a href="index.php">Home</a></li>
<li class="MyMenuItem"><a href="papers.php">Papers</a></li>
<li class="MyMenuItem"><a href="license.php">License</a></li>
<li class="MyMenuItem"><a href="faq.php">FAQ</a></li>
<li class="MyMenuItem"><a href="code.php">Software</a></li>
<li class="MyMenuItem"><a href="links.php">Links</a></li>
</ul>
</div>

<div id="body">
<h1 style="clear:left">Software for Matlab</h1>

<img src="mxWrapper-2011/2dplot.gif" style="float:right" width=300>

<h2>mxWrapper: a replacement for mwArray</h2>

<p>Around 2004, Mathworks discontinued its support for C++ programs to directly call into the internals of Matlab via a C++ class called mwArray. You can still <a href="http://www.codeproject.com/Articles/4219/Solving-Engineering-Problems-Using-MATLAB-C-Math-L">find websites telling people to use mwArray</a>; seeing #include "matlab.hpp" is a clear sign of this problem. Instead, the Matlab Engine was intended to be the supported interface, via mxArray, which does not allow any direct computations. mwArray was reimplemented for the Matlab Compiler interface, which doesn't work with most of the Matlab code that I tried it on.</p>

<p>In 2010, this became my problem. As part of maintaining a large, legacy C++ application, I needed the to continue to use the original functionality of mwArray, but the only sensible way to do it was through the Matlab Engine. So I wrote a fairly complex C++ wrapper class that restored the functionality I needed via mxArray and the Matlab Engine. You can <a href="mxWrapper-2011/mxWrapper-2011.zip">download the mxWrapper class here</a>, or you can get it <a href="http://www.mathworks.com/matlabcentral/fileexchange/28331-replacement-for-mwarray-using-matlab-engine">from the Mathworks File Exchange</a>. Eventually, I modified the legacy application so that most of the challenging math was occuring inside Matlab, which was called via mxWrapper, and the legacy code focused on data acquisition, low level drivers, proprietary file format support, etc. </p>

<p>I included an example MFC program that demonstrates how mxWrapper works. It could still be useful for C++ programs that need to call the full functionality of Matlab, which isn't available through the Matlab Compiler. See screenshot to the side. If you replaced the Windows-specific multi-threading primitives (CCriticalSection), I'm pretty sure you could get mxWrapper to work under any Matlab platform (Apple, Unix, etc.).</p>

<h2 style="clear:both">Sudoku Solver</h1>

<p>For fun I wrote a Sudoku solver in C++. It can solve a decent number of Sudoku puzzles, but not all of them because the general Sudoku problem is NP-complete. Sudoku turns out to be <a href="https://en.wikipedia.org/wiki/Exact_cover#Sudoku">equivalent to solving an exact cover problem</a>, which Donald Knuth wrote about. I really can't compare to Knuth's brilliant algorithms, so my code is just a toy. I came up with the algorithms in the code from my own intuition.</p>

<p><a href="misc/sudokusolver.cpp">Download the Sudoku solver here</a>. It should compile with any recent C++ compiler. Some example problems are given <a href="misc/sudoku.txt">in this input file</a>, and the solutions are in <a href="misc/soln.txt">in this output file</a>. </p>

<h3>Example Input problem:</h3>

<p>This is a relatively easy Sudoku problem because recursive guessing isn't required to solve it:</p>

<pre>
 _______________________
| 4 8 0 | 0 0 6 | 9 0 2 |
| 0 0 2 | 0 0 8 | 0 0 1 |
| 9 0 0 | 3 7 0 | 0 6 0 |
------------------------
| 8 4 0 | 0 1 0 | 2 0 0 |
| 0 0 3 | 7 0 4 | 1 0 0 |
| 0 0 1 | 0 6 0 | 0 4 9 |
------------------------
| 0 2 0 | 0 8 5 | 0 0 7 |
| 7 0 0 | 9 0 0 | 6 0 0 |
| 6 0 9 | 2 0 0 | 0 1 8 |
 -----------------------
</pre>

<p>The one and only solution to this problem is:</p>

<pre>
 _______________________
| 4 8 7 | 1 5 6 | 9 3 2 |
| 3 6 2 | 4 9 8 | 7 5 1 |
| 9 1 5 | 3 7 2 | 8 6 4 |
------------------------
| 8 4 6 | 5 1 9 | 2 7 3 |
| 5 9 3 | 7 2 4 | 1 8 6 |
| 2 7 1 | 8 6 3 | 5 4 9 |
------------------------
| 1 2 4 | 6 8 5 | 3 9 7 |
| 7 3 8 | 9 4 1 | 6 2 5 |
| 6 5 9 | 2 3 7 | 4 1 8 |
 -----------------------
</pre>

<p>You can deduce the solution by placing 2s and 4s by negative constraints (only 1 per row, column, or box), and then applying positive constraints (e.g., there must be a 7 in every row, column, or box). My code solves this puzzle by alternating between these ad hoc algorithms (negative and positive constraints).</p>


<h2 style="clear:both">Radon Transform Code</h1>

<p style="clear: both">Coming soon.</p>

<p style="clear: both">&nbsp;</p>

</div>
</div>

<!-- Google Analytics -->
<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-40728104-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

</body></html>
