<html><head>
<link rel="stylesheet" type="text/css" media="all" href="papers.css">
<link rel="stylesheet" type="text/css" media="screen" href="papers-screen.css">
<link rel="stylesheet" type="text/css" media="print" href="papers-print.css">
<title>Fast Fat/Water Decomposition Using GPU Computation and Newton's Method</title>
</head>
<body>

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


<h1>Fast Fat/Water Decomposition Using GPU Computation and Newton's Method</h1>

<p>David Johnson, Sreenath Narayan, Chris Flask, David Wilson</p>

<p>ISMRM 2010, Poster Presentation #3156. <a href="PDF/2010-ISMRM-Poster-GPU-3156_633.pdf">The poster is available here [PDF].</a></p>

<h2>Abstract</h2>

<p>An improved fat/water estimation technique was developed using a formulation similar to the Iterative Decomposition of Water and Fat with Echo Asymmetry and Least-squares estimation method and Graphics Computational Units (IDEAL-GPU). The IDEAL-GPU technique produced robust fat and water images quickly and efficiently using a vectorized equation implemented on graphics cards. In addition, our implementation used binary weighted planar extrapolation for robust estimation in the face of large field variations on a high field, small animal scanner. Fast computation will become even more significant as the trend towards high resolution, whole body mouse and human scanning continues.</p>

<h2>Introduction</h2>

<p>We are developing quantitative MRI techniques to quantify fat depots (e.g., visceral, subcutaneous, hepatic, muscular) to determine the role of genetic, environmental, and therapeutic factors on lipid accumulation, metabolism, and disease states. We have shown previously that conventional clinical scanners can provide sufficient image quality for rats and larger animals [1]. However, high field MRI scanners (7T-11T) are needed to produce the high resolution images that provide the basis for accurate delineation between visceral and subcutaneous lipid compartments in mice [2]. However, the data processing time is significant because 3-6 image sets at variable echo times must be acquired resulting in &gt;1GB of data.&nbsp; This requires over 1 hour of processing time for each animal. The purpose of this study was to develop a method to more quickly produce fat and water estimates enabling rapid MRI phenotyping. Our initial results show a 2- to 12-fold reduction in processing time when GPU computations are used, which greatly eases the burden of the IDEAL reconstruction time.</p>

<h2>Methods</h2>

<p>Three 26 week old C57BL/6J male mice were scanned using an asymmetric spin echo acquisition (aSE) for IDEAL [3], which was implemented for imaging mice on a 7T/30cm Bruker Biospec scanner [4]. We reformulated the IDEAL equations using vectorization and implemented the algorithm using a Matlab GPU library (Accelereyes Jacket). In contrast to previous IDEAL per-pixel algorithms, vectorized IDEAL evaluates the residuals (J) of each estimate of the field inhomogeneity, &psi;(x), in each of the pixels of the image (x, x+1, x+2, ... x+N*M), all at once. The observation matrix A ([1 e^(j2&pi;*TE(1)*1050Hz); 1 e^(j2&pi;*TE(2)*1050Hz); 1 e^(j2&pi;*TE(3)*1050Hz)]), and a temporary matrix T (the per-element product of the observed signals S(x,TE) and &psi;(x)), are also calculated, as per Eqs (1) and (2).</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block">
<mrow>
<munder>
  <mfenced open="[" close="]" separators=",">
    <mrow>
      <mtable>
        <mtr>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>1</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>1</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>2</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>2</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>3</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>3</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
      </mtable>
    </mrow>
  </mfenced>
        <munder>
                <mo>&UnderBrace;</mo>
              <mi>T</mi>
        </munder>
</munder>
  <mo>=</mo>
<munder>
  <mfenced open="[" close="]" separators=",">
    <mrow>
      <mtable>
        <mtr>
          <mtd>
            <mi>S</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>1</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>S</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
              <mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>1</mn>
                </msub>
              </mrow>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <mi>S</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>2</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>S</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
              <mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>2</mn>
                </msub>
              </mrow>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <mi>S</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>3</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>S</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
              <mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>3</mn>
                </msub>
              </mrow>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
      </mtable>
    </mrow>
  </mfenced>
        <munder>
                <mo>&UnderBrace;</mo>
              <mi>S</mi>
        </munder>
</munder>
  <mo>*</mo>
<munder>
  <mfenced open="[" close="]" separators=",">
    <mrow>
      <mtable>
        <mtr>
          <mtd>
            <msup>
                    <mo>&ExponentialE;</mo>
                <mrow>
                  <mo>-</mo>
                  <mn>2</mn>
                  <mi>j</mi>
                  <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                  <mfenced open="(" close=")" separators=",">
                    <mrow>
                      <mi>x</mi>
                    </mrow>
                  </mfenced>
                  <msub>
                          <mi>TE</mi>
                        <mn>1</mn>
                  </msub>
                </mrow>
            </msup>
          </mtd>
          <mtd>
            <msup>
                    <mo>&ExponentialE;</mo>
                <mrow>
                  <mo>-</mo>
                  <mn>2</mn>
                  <mi>j</mi>
                  <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                  <mfenced open="(" close=")" separators=",">
                    <mrow>
                      <mi>x</mi>
		      <mo>+</mo>
		      <mn>1</mn>
                    </mrow>
                  </mfenced>
                  <msub>
                          <mi>TE</mi>
                        <mn>1</mn>
                  </msub>
                </mrow>
            </msup>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <msup>
                    <mo>&ExponentialE;</mo>
                <mrow>
                  <mo>-</mo>
                  <mn>2</mn>
                  <mi>j</mi>
                  <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                  <mfenced open="(" close=")" separators=",">
                    <mrow>
                      <mi>x</mi>
                    </mrow>
                  </mfenced>
                  <msub>
                          <mi>TE</mi>
                        <mn>2</mn>
                  </msub>
                </mrow>
            </msup>
          </mtd>
          <mtd>
            <msup>
                    <mo>&ExponentialE;</mo>
                <mrow>
                  <mo>-</mo>
                  <mn>2</mn>
                  <mi>j</mi>
                  <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                  <mfenced open="(" close=")" separators=",">
                    <mrow>
                      <mi>x</mi>
		      <mo>+</mo>
		      <mn>1</mn>
                    </mrow>
                  </mfenced>
                  <msub>
                          <mi>TE</mi>
                        <mn>2</mn>
                  </msub>
                </mrow>
            </msup>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <msup>
                    <mo>&ExponentialE;</mo>
                <mrow>
                  <mo>-</mo>
                  <mn>2</mn>
                  <mi>j</mi>
                  <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                  <mfenced open="(" close=")" separators=",">
                    <mrow>
                      <mi>x</mi>
                    </mrow>
                  </mfenced>
                  <msub>
                          <mi>TE</mi>
                        <mn>3</mn>
                  </msub>
                </mrow>
            </msup>
          </mtd>
          <mtd>
            <msup>
                    <mo>&ExponentialE;</mo>
                <mrow>
                  <mo>-</mo>
                  <mn>2</mn>
                  <mi>j</mi>
                  <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                  <mfenced open="(" close=")" separators=",">
                    <mrow>
                      <mi>x</mi>
		      <mo>+</mo>
		      <mn>1</mn>
                    </mrow>
                  </mfenced>
                  <msub>
                          <mi>TE</mi>
                        <mn>3</mn>
                  </msub>
                </mrow>
            </msup>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
      </mtable>
    </mrow>
  </mfenced>
        <munder>
                <mo>&UnderBrace;</mo>
              <mi>&Psi;</mi>
        </munder>
</munder>
</mrow>
</math>

</div>
<div style="float:right">
	<p align="right">(1)</p>
</div>
<p style="clear:both"></p>
</div>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block">
<mrow>
  <mfenced open="[" close="]" separators=",">
    <mrow>
      <mtable>
        <mtr>
          <mtd>
            <mi>J</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                <mfenced open="(" close=")" separators=",">
                  <mrow>
                    <mi>x</mi>
                  </mrow>
                </mfenced>
              </mrow>
            </mfenced>
          </mtd>
          <mtd>
            <mi>J</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>&psi;</mi><mo>&ApplyFunction;</mo>
                <mfenced open="(" close=")" separators=",">
                  <mrow>
                    <mi>x</mi>
                    <mo>+</mo>
                    <mn>1</mn>
                  </mrow>
                </mfenced>
              </mrow>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
      </mtable>
    </mrow>
  </mfenced>
  <mo>=</mo>
  <msub>
        <mrow>
          <mfenced open="|" close="|" separators=",">
            <mrow>
              <mfenced open="(" close=")" separators=",">
                <mrow>
                  <mi>I</mi>
                  <mo>-</mo>
                  <mi>A</mi>
                  <msup>
                          <mi>A</mi>
                        <mo>&dagger;</mo>
                  </msup>
                </mrow>
              </mfenced>
  <mfenced open="[" close="]" separators=",">
    <mrow>
      <mtable>
        <mtr>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>1</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>1</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>2</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>2</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
        <mtr>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
                <mi>x</mi>
                <msub>
                        <mi>TE</mi>
                      <mn>3</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mi>T</mi><mo>&ApplyFunction;</mo>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>+</mo>
                <mn>1</mn>
              </mrow>
                <msub>
                        <mi>TE</mi>
                      <mn>3</mn>
                </msub>
            </mfenced>
          </mtd>
          <mtd>
            <mo>&CenterDot;&CenterDot;&CenterDot;</mo>
          </mtd>
        </mtr>
      </mtable>
    </mrow>
  </mfenced>
            </mrow>
          </mfenced>
        </mrow>
        <mn>2</mn>
  </msub>
</mrow>
</math>

</div>
<div style="float:right">
	<p align="right">(2)</p>
</div>
<p style="clear:both"></p>
</div>


<p>The first and second partial derivatives of J with respect to &psi; were evaluated analytically, and the residuals were independently minimized in each pixel using our GPU implementation of Newton&#39;s method. Newton&#39;s method &quot;jumps&quot; to the minimum (apex) of a parabola determined by the ratio of the first and second derivatives (Fig 1). The method was tested on the three mouse datasets each with TEs corresponding to p/6, 5p/6, and 3p/2 radian shifts between fat and water. IDEAL-GPU was run 11 times and the execution times excluding the first were averaged. The effects of different data sizes on the CPU and GPU execution times were tested by downsampling the images from the acquired 512x512 size along the phase encoding direction.</p>

<h2>Results</h2>

<p>The execution time of running the reconstruction was reduced by 2- to 12-fold using our GPU algorithm, corresponding to a reduction from 4 minutes per image to &lt;10 seconds per image (Fig 2). The relative speedup of the GPU increased to almost 12X for larger images (Fig 3), but no additional gains were observed for images bigger than 512x512 pixels. The use of single precision floating point calculations on both CPU and GPU did not visibly affect the quality of the reconstructed images.</p>

<h2>Discussion</h2>

<p>IDEAL provides excellent fat and water estimates, but the processing thrice the data of one acquisition is a burden. Using 6 or more TEs for multi-peak IDEAL [5] is an even greater computational challenge. IDEAL-GPU addresses these problems by reformulating the estimation as a series of efficient matrix multiplications. IDEAL-GPU is not dependent on a specific video card, and we anticipate further speedups with the development of newer video cards with higher clock rates and more processor elements. Also, additional video cards can be used in parallel to reconstruct multiple images simultaneously, allowing for even more scalability.</p>

<h2>References and Acknowledgements.</h2> [1] Johnson et al. JMRI 2008; 28(4):915-927. [2] Johnson et al. accepted for publication JMRI 2009. [3] Reeder et al. MRM 2005; 54(3): 636-644. [4] Johnson et al., ISMRM 2009:2682. [5] Kijowski et al. JMRI 2008; 29(2): 436-442. This work was supported by NCI R24-CA110943 (Northeast Ohio Animal Imaging Resource Center), NIH F30DK082132, NIH R01-EB004070, and NIH 1T32EB007509-01 (Interdisciplinary Biomedical Imaging Training Program).</p>

<a id="Fig1"><div class="figure">
	<img src="images/ismrm2010-gpu-1.png" />
<p class="figureCaption"><span class="figureName">Fig 1.</span> Newton's method finds the minimum quickly by fitting a local parabola.</p> 
</div></a>

<a id="Fig2"><div class="figure">
	<img src="images/ismrm2010-gpu-2.png" />
<p class="figureCaption"><span class="figureName">Fig 2.</span> GPU execution times (solid line) were much faster than the CPU, even when multiple CPUs were used (multiple broken lines).</p> 
</div></a>

<a id="Fig3"><div class="figure">
	<img src="images/ismrm2010-gpu-3.png" />
<p class="figureCaption"><span class="figureName">Fig 3.</span> The GPU advantage over the CPU continued to improve for up to 512x512 images.</p> 
</div></a>



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

