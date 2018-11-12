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
<?php include_once("menu.html") ?>

<div id="body">
<h1 style="clear:left">Website Links</h1>

<h2>Tomographic Code</h2>

<p>For performing the forward or adjoint Radon transform.</p>

<ul>
<li><a href="http://www.mathworks.com/help/images/ref/radon.html">Matlab radon()</a> and <a href="http://www.mathworks.com/help/images/ref/radon.html">iradon()</a>. 2D only; can't use arbitrary sets of angles. Fast C/MEX code, but the operators are mismatched (pixel-based forward operator and ray-based adjoint operator), which introduces artificial high frequency noise.</li>
<li><a href="http://www-user.tu-chemnitz.de/~potts/nfft/">Potts nonuniform FFT</a>. The nonuniform FFT is more general than the Radon transform, but the <a href="https://en.wikipedia.org/wiki/Projection-slice_theorem">Fourier Slice Theorem</a> can be used to convert the tomographic problem into a NUFFT. The curse of dimensionality imposes a memory limitation on 3D or 4D implementations, and there can be new artifacts due to the Fourier domain interpolation kernel.</li>
<li><a href="http://web.eecs.umich.edu/~fessler/">Jeff Fessler's Image reconstruction toolbox</a> (U Michigan). Excellent Radon transform and NUFFT code, mostly 2D and some 3D.</li>
<li><a href="http://petertoft.dk/PhD/">Peter Toft's PhD thesis</a> and programs. Pretty decent code, but I couldn't get it working under Windows.</li>
</ul>

<h2>EPR Imaging Research Groups</h2>

<p>There are only a relatively small number of EPRI research groups. Sorry if I missed anyone. Alphabetical order.</p>

<ul>
<li><a href="http://schulich.technion.ac.il/Aharon_Blank.htm">Aharon Blank</a> et al. at Technion - Israel Institute of Technology.</li>
<li><a href="http://www.uclouvain.be/en-rema">Gallez Bernard</a> et al. at Universite catholique de Louvain. </li>
<li><a href="http://ccr.cancer.gov/staff/staff.asp?profileid=5555">Murali Krishna Cherukuri</a> et al. at National Cancer Institute.</li>
<li><a href="https://portfolio.du.edu/geaton">Gareth Eaton</a> et al. at University of Denver. </li>
<li><a href="http://epri.uchicago.edu/html/halpern.html">Howard J. Halpern</a> et al. at University of Chicago. </li>
<li><a href="http://www.bme.ist.hokudai.ac.jp/BPE/Hirata.html">Hiroshi Hirata</a> et al. at Hokkaido University</li>
<li><a href="http://www.mcw.edu/EPRCenter/FacultyandStaff/JamesSHyde.htm">James S. Hyde</a> et al. at Medical College of Wisconsin</li>
<li><a href="http://www.kfti.knc.ru/eng/about/index.html">Kev Minullinovich Salikhov</a> et al. at Zavoisky Physical-Technical Institute of the Kazan Scientific Center of the Russian Academy of Sciences</li>
<li><a href="http://www.dartmouth.edu/~eprctr/">Harold Swartz</a> et al. at Dartmouth University</li>
<li><a href="http://www.bruker.com/products/mr/epr.html">Ralph Weber</a> et al. at Bruker</li>
<li><a href="https://heartlung.osu.edu">Jay Zweier</a> et al. at the Ohio State University</li>
</ul>

<p>Conferences and societies.</p>

<ul>
<li><a href="http://www.cvent.com/events/41st-annual-isott-meeting-epr-2013/event-summary-f2331d59bade408eaf18d20bd986ec35.aspx">International ISOTT and EPR Conferences</a>; bi-annual.</li>
<li><a href="http://www.epr-newsletter.ethz.ch/">The International EPR (ESR) Society</a> has a newsletter with most of the big players.</li>
<li><a href="http://www.ismrm.org/">International Society for Magnetic Resonance in Medicine (ISMRM)</a> has a few EPR posters for historical reasons.</li>
</ul>

<p style="clear: both">&nbsp;</p>

</div>
</div>

<!-- Google Analytics -->
<?php include_once("analyticstracking.php") ?>

</body></html>
