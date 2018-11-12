<html><head>
<link rel="stylesheet" type="text/css" media="all" href="papers.css">
<link rel="stylesheet" type="text/css" media="screen" href="papers-screen.css">
<link rel="stylesheet" type="text/css" media="print" href="papers-print.css">
<title>Compressed Sensing of Spatial Electron Paramagnetic Resonance Imaging</title>
<!-- script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=MML_HTMLorMML"> </script -->
<script type="text/javascript" src="mathjax-MathJax-24a378e/MathJax.js?config=MML_HTMLorMML"> </script>
</head>
<body>

<div id="outerContainer">

<!-- Site Navigation Menu -->
<?php include_once("menu.html") ?>

<div id="body">

<h1>Compressed Sensing of Spatial Electron Paramagnetic Resonance Imaging</h1>
<p>David H. Johnson, Rizwan Ahmad, Guanglong He, Alexandre Samouilov, Jay L. Zweier</p>

<p>This is an author's electronic pre-print of the following publication. MRM allows pre-prints to be shared through individual author's websites; for terms, please see this website's license. Please cite the published work as: </p>


<p><span class="Title">Compressed Sensing of Spatial Electron Paramagnetic Resonance Imaging.</span> Johnson DH, Ahmad R, He G, Samouilov A, Zweier JL. Magn Reson Med 2013. Pubmed: <a href="https://www.ncbi.nlm.nih.gov/pubmed/?dopt=Citation">not assigned yet</a>. <a href="http://dx.doi.org/10.1002/mrm.24966">Journal's version</a>. </p>

<p>Address for correspondence: Jay L. Zweier, MD. <a href="mailto:Jay.Zweier@osumc.edu">Jay.Zweier@osumc.edu</a>.</p>

<h2>ABSTRACT</h2>

<p><strong>Purpose:</strong> To improve image quality and reduce data requirements for spatial electron paramagnetic resonance imaging (EPRI) by developing a novel reconstruction approach using compressed sensing (CS).</p>

<p><strong>Methods:</strong> EPRI is posed as an optimization problem, which is solved using regularized least-squares with sparsity promoting penalty terms, consisting of the l1 norms of the image itself and the Total Variation of the image. Pseudo-random sampling was employed to facilitate recovery of the sparse signal. The reconstruction was compared to the traditional Filtered Back-Projection reconstruction for simulations, phantoms, isolated rat hearts, and mouse GI tracts labeled with paramagnetic probes.</p>

<p><strong>Results: </strong>A combination of pseudo-random sampling and CS was able to generate high-fidelity EPR images at high acceleration rates. For 3D phantom imaging, CS-based EPRI showed little visual degradation at 9-fold acceleration. In rat heart datasets, CS-based EPRI produced high quality images with 8-fold acceleration. A high resolution mouse GI tract reconstruction demonstrated a visual improvement in spatial resolution and a doubling in SNR.</p>

<p><strong>Conclusion:</strong> A novel 3D EPRI reconstruction utilizing compressed sensing was developed and offers superior SNR and reduced artifacts from highly undersampled data.</p>

<h2>INTRODUCTION</h2>

<p>Continuous wave spatial electron paramagnetic resonance (EPR) imaging is a form of tomography where a 3D object is recovered from projections blurred by a known point spread function (i.e., the spatially invariant electron spectrum) (<a href="#_ENREF_1">1</a>,<a href="#_ENREF_2">2</a>). EPR has the potential to measure in vivo free radicals, which provide important physiological information (e.g., oxygen, pH, and cellular redox status) (<a href="#_ENREF_3">3-6</a>). Spatial EPRI can be used for studies of probe uptake, clearance, metabolism, and biodistribution. Purely spatial EPR imaging can determine the rate of clearance of a probe, such as a nitroxide, which is useful for characterizing tumors redox state. Dynamic changes in signal intensity are important for the study of cancer metabolism or myocardial ischemia and reperfusion (<a href="#_ENREF_7">7-13</a>). The absence of EPR probe signal or absence of metabolism may itself be informative; for example, in myocardial ischemia spatial EPRI allows visualization of the risk region and region of necrosis (<a href="#_ENREF_8">8</a>). This purely spatial EPRI experiment is sufficient to determine where the loss of viable myocardium has occurred.</p>

<p>Historically, applications of spatial EPRI have been limited by a lack of projections, low spatial resolution, and limited SNR. Recent advances have improved the quality of EPR images by expediting the acquisition using rapid scan or spinning gradient, choosing more effective sets of projections to acquire, and developing narrow linewidth probes with high spin densities (<a href="#_ENREF_14">14-16</a>). Yet, the image reconstruction for in vivo experiments is still based on Filtered Back-Projection (FBP) or Algebraic Reconstruction Techniques (ART), both of which require a relatively large number of projections. Reconstructions based on the maximum entropy method and Tikhonov regularization recently demonstrated improvements to spectral-spatial EPR reconstructions in phantom experiments (<a href="#_ENREF_17">17-19</a>). Another recent approach is to restrict the EPR probe to multiple discrete sites with non-overlapping spatial locations and perform a lineshape-fitting based reconstruction (<a href="#_ENREF_20">20</a>,<a href="#_ENREF_21">21</a>). There is a potential to further improve spatial in vivo EPR imaging with diffuse probes by exploiting the inherent sparsity in the images, and this is the main focus of this study.</p>

<p>Compressed Sensing (CS) has been used to reconstruct images from only a small amount of acquired data, yielding a large reduction in acquisition time (<a href="#_ENREF_22">22-24</a>). For example, MRI angiography has been accelerated by a factor of 10, which enables imaging of the entire heart in a single breath-hold acquisition (<a href="#_ENREF_25">25</a>). The requirements for CS are that the image is sparse in some domain (e.g., finite differences between adjacent pixels, wavelets, etc.), the noise in the image is incoherent, and a nonlinear reconstruction is used to recover the image. We propose that a CS reconstruction can produce high quality EPR images from a fraction of the number of projections which would normally be required. CS has been applied to spectral-spatial EPRI before, but only in the context of multisite oximetry with known lineshape (<a href="#_ENREF_21">21</a>,<a href="#_ENREF_26">26</a>,<a href="#_ENREF_27">27</a>). The CS methods presented in this work are less restrictive as they do not strictly rely on the spatially sparse distributions encountered in multisite oximetry. Another limitation of the multisite CS approach is the requirement to uniquely identify the parameters of the lineshape model, which can be difficult in mixtures of Lorentzian and Gaussian shapes with both dispersion and absorption components.&nbsp;</p>

<p>The goal of this study was to reduce the number of projections required for 3D spatial EPRI by the development and implementation of a reconstruction which uses l1 penalty terms in the optimization and also explicitly incorporates the measured EPR spectrum into the signal model. An exact adjoint operator is defined and used to recover deblurred images via iterative estimation. Sparsifying transformations for EPRI are proposed, and the effects of incoherent sampling are investigated by comparing different gradient angle distributions. The CS reconstruction is tested on a variety of typical EPR imaging experiments using common probes and compared to the FBP reconstruction.</p>

<h2>THEORY</h2>

<h3>Problem Formulation</h3>

<p>For spatial EPRI, the forward model is given by Eq (1):</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <mi>y</mi>
  <mo>=</mo>
  <mi>C</mi>
  <mi>R</mi>
  <mi>x</mi>
</mrow>
</math>

</div>
<div style="float:right">
	<p align="right">(1)</p>
</div>
<p style="clear:both"></p>
</div>


<p>where the 3D image volume (<em>x</em>) is projected by the Radon transform (<em>R</em>) and those projections are blurred by the convolution operator (<em>C</em>) using the known spectrum to produce the observed projections (<em>y</em>). In the classic FBP reconstruction used in EPRI, image is recovered by applying multiple disjoint steps</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <mi>x</mi>
  <mo>=</mo>
  <msup>
          <mi>R</mi>
        <mn>-1</mn>
  </msup>
  <msup>
          <mi>C</mi>
        <mn>-1</mn>
  </msup>
  <mi>y</mi>
  <mo>&thkap;</mo>
  <msup>
          <mi>R</mi>
        <mo>*</mo>
  </msup>
  <mfrac>
    <mrow>
      <msup>
              <mi>d</mi>
            <mn>2</mn>
      </msup>
    </mrow>
    <mrow>
      <msup>
              <mi>ds</mi>
            <mn>2</mn>
      </msup>
    </mrow>
  </mfrac>
  <mi>W</mi>
  <msup>
          <mi>C</mi>
        <mn>-1</mn>
  </msup>
  <mi>y</mi>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(2)</p>
</div>
<p style="clear:both"></p>
</div>

<p>where the second derivative with respect to projection coordinate (<em>s</em>) and projection weighting (<em>W</em>) operators are needed along with the deconvolution operator (<em>C-1</em>) and the&nbsp; backprojection operator, <em>R*, </em>&nbsp;which is adjoint of <em>R</em>. The weighting operator is necessary when the distribution of projections is not uniform (<a href="#_ENREF_14">14</a>). Deconvolution, <em>C-1y</em>, can be performed in Fourier domain using point-by-point division of the Fourier transform of <em>y </em>with the Fourier transform of the spectrum. This implementation, however, amplifies noise and may lead to division-by-zero problems (<a href="#_ENREF_1">1</a>). Therefore, a lowpass filter generally precedes the point-by-point division in the Fourier domain, yielding</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <msup>
          <mi>C</mi>
        <mn>-1</mn>
  </msup>
  <mi>y</mi>
  <mo>&thkap;</mo>
  <msup>
          <mi>F</mi>
        <mn>-1</mn>
  </msup>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <mfrac>
        <mrow>
          <mi>V</mi>
          <mfenced open="(" close=")" separators=",">
            <mrow>
              <mi>F</mi>
              <mi>y</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mrow>
          <mi>F</mi>
          <mi>z</mi>
        </mrow>
      </mfrac>
    </mrow>
  </mfenced>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(3)</p>
</div>
<p style="clear:both"></p>
</div>

<p>where F denotes the discrete Fourier transform, <em>z</em> indicates the EPR spectrum, and <em>V </em>&nbsp;represents a lowpass filter in the Fourier domain.&nbsp;</p>

<p>The FBP reconstruction is non-iterative and computationally fast. However, the limitations of a finite number of projections and involvement of lowpass filter <em>V</em> often result in a loss of spatial resolution, streaking artifacts, and SNR degradation. Nevertheless, it remains the mainstay of EPR imaging experiments because it is simple and fast.</p>

<p>We propose a novel EPRI reconstruction based on searching for the solution (<em>xCS</em>), which is not only consistent with the acquired data but only prefers piece-wise constancy and spatial sparsity. This can be achieved by introducing l1 regularization terms to the data fidelity term of the cost function. This approach, which exploits compressibility of EPR images, allows robust reconstruction from a small number of projections. Deconvolution is entirely avoided by incorporating the convolution into the signal model. Instead, the reconstruction directly uses the measured first derivative EPR projections without needing integration, thresholding, or other denoising procedures. Therefore, we solve the optimization problem given by Eq (4):</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <msub>
          <mi>x</mi>
        <mi>CS</mi>
  </msub>
  <mo>=</mo>
  <mi>arg</mi><mo>&ApplyFunction;</mo>
  
    <mrow>
      <munder>
            <mrow>
              <mi>min</mi><mo>&ApplyFunction;</mo>
            </mrow>
            <mi>x</mi>
      </munder>
    </mrow>
  
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>C</mi><mo>&ApplyFunction;</mo>
              <mi>R</mi><mo>&ApplyFunction;</mo>
              <mi>x</mi>
              <mo>-</mo>
              <mi>y</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mn>2</mn>
  </msub>
  <mo>+</mo>
  <msub>
          <mi>&lambda;</mi>
        <mn>1</mn>
  </msub>
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>x</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mn>1</mn>
  </msub>
  <mo>+</mo>
  <msub>
          <mi>&lambda;</mi>
        <mn>2</mn>
  </msub>
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>TV</mi><mo>&ApplyFunction;</mo>
              <mfenced open="(" close=")" separators=",">
                <mrow>
                  <mi>x</mi>
                </mrow>
              </mfenced>
            </mrow>
          </mfenced>
        </mrow>
        <mn>1</mn>
  </msub>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(4)</p>
</div>
<p style="clear:both"></p>
</div>

<p>where TV stands for the Total Variation. The TV norm favors piece-wise constant images, and it is frequently applied to image reconstructions of MRI and x-ray computed tomography data (<a href="#_ENREF_25">25</a>). The norms given above are defined as:</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>x</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mi>p</mi>
  </msub>
  <mo>=</mo>
  <msup>
        <mrow>
          <mfenced open="(" close=")" separators=",">
            <mrow>
              <munderover>
                      <mo>&Sum;</mo>
                  <mrow>
                    <mi>i</mi>
                    <mo>=</mo>
                    <mn>1</mn>
                  </mrow>
                    <mi>N</mi>
              </munderover>
              <msup>
                    <mrow>
                      <mfenced open="|" close="|" separators=",">
                        <mrow>
                          <msub>
                                  <mi>x</mi>
                                <mi>i</mi>
                          </msub>
                        </mrow>
                      </mfenced>
                    </mrow>
                    <mi>p</mi>
              </msup>
            </mrow>
          </mfenced>
        </mrow>
        <mfrac>
          <mrow>
            <mn>1</mn>
          </mrow>
          <mrow>
            <mi>p</mi>
          </mrow>
        </mfrac>
  </msup>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(5)</p>
</div>
<p style="clear:both"></p>
</div>

<p>where <em>p</em> is the order of the norm (e.g., p=1 for l1) and <em>N</em> is the number of elements in the vector <em>x</em>. The first term with the l2 norm ensures that the solution is consistent with the acquired projections. The weights <em>&lambda;</em><sub>1</sub> and <em>&lambda;</em><sub>2</sub> reflect the tradeoffs between favoring solutions which are mostly zeros and more strongly piece-wise constant, respectively. For the degenerate case of <em>&lambda;</em>1 = <em>&lambda;</em>2 = 0, the reconstruction is equivalent to the Algebraic Reconstruction Technique with lineshape information (<a href="#_ENREF_28">28</a>).</p>

<h3>CS-based EPRI Reconstruction</h3>

<p>To solve the optimization problem posed by Eq (4), we introduce a temporary image (<em>u</em>) and use an alternating minimization algorithm to solve the two sub-problems:</p>


<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <mi>arg</mi><mo>&ApplyFunction;</mo>
  
    <mrow>
      <munder>
            <mrow>
              <mi>min</mi><mo>&ApplyFunction;</mo>
            </mrow>
            <mi>x</mi>
      </munder>
    </mrow>
  
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>C</mi><mo>&ApplyFunction;</mo>
              <mi>R</mi><mo>&ApplyFunction;</mo>
              <mi>x</mi>
              <mo>-</mo>
              <mi>y</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mn>2</mn>
  </msub>
  <mo>+</mo>
  <msub>
          <mi>&lambda;</mi>
        <mn>1</mn>
  </msub>
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>x</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mn>1</mn>
  </msub>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(6)</p>
</div>
<p style="clear:both"></p>
</div>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <mi>arg</mi><mo>&ApplyFunction;</mo>
  
    <mrow>
      <munder>
            <mrow>
              <mi>min</mi><mo>&ApplyFunction;</mo>
            </mrow>
            <mi>u</mi>
      </munder>
    </mrow>
  
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>x</mi>
              <mo>-</mo>
              <mi>u</mi>
            </mrow>
          </mfenced>
        </mrow>
        <mn>2</mn>
  </msub>
  <mo>+</mo>
  <msub>
          <mi>&lambda;</mi>
        <mn>2</mn>
  </msub>
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>TV</mi><mo>&ApplyFunction;</mo>
              <mfenced open="(" close=")" separators=",">
                <mrow>
                  <mi>u</mi>
                </mrow>
              </mfenced>
            </mrow>
          </mfenced>
        </mrow>
        <mn>1</mn>
  </msub>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(7)</p>
</div>
<p style="clear:both"></p>
</div>

<p>The solution to Eq (6) fits the observed projections and also favors images which are mostly zeros. Solving Eq (7) performs TV denoising of the current estimate of the image. Both problems are solved using the Fast Iterative Shrinkage-Thresholding Algorithm (FISTA) (<a href="#_ENREF_29">29</a>). The intermediate result (<em>z</em>) of TV denoising is used to re-initialize the solution of Eq (6), which reinforces the data consistency and l1 norm. The reconstruction alternates between solving Eq (6) and (7) until the solution converges, which occurs when the l1 norm of the current estimate changes less than a fixed threshold in two successive iterations (e.g., 0.1%).</p>

<p>FISTA is used to solve Eq (6) using a Landweber update to the current estimate of the image (<em>z</em>) followed by the shrinkage operator (S):</p>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <msub>
          <mi>x</mi>
        <mi>n</mi>
  </msub>
  <mo>=</mo>
  <mi>S</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <msub>
              <mi>z</mi>
            <mi>n</mi>
      </msub>
      <mo>-</mo>
      <mi>&mu;</mi>
      <mfenced open="(" close=")" separators=",">
        <mrow>
          <msup>
                <mrow>
                  <mi>R</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <msup>
                <mrow>
                  <mi>C</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <mi>C</mi><mo>&ApplyFunction;</mo>
          <mi>R</mi><mo>&ApplyFunction;</mo>
          <msub>
                  <mi>z</mi>
                <mi>n</mi>
          </msub>
          <mo>-</mo>
          <msup>
                <mrow>
                  <mi>R</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <msup>
                <mrow>
                  <mi>C</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <mi>y</mi>
        </mrow>
      </mfenced>
    </mrow>
    <mrow>
      
        <mspace />
      
      <mfrac>
        <mrow>
          <msub>
                  <mi>&lambda;</mi>
                <mn>1</mn>
          </msub>
          <mi>&mu;</mi>
        </mrow>
        <mrow>
          <mn>2</mn>
        </mrow>
      </mfrac>
    </mrow>
  </mfenced>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(8)</p>
</div>
<p style="clear:both"></p>
</div>

<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <mi>S</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <mi>x</mi>
    </mrow>
    <mrow>
      <mi>&lambda;</mi>
    </mrow>
  </mfenced>
  <mo>=</mo>
  <mi>sign</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <mi>x</mi>
    </mrow>
  </mfenced>
  <mi>max</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <mfenced open="|" close="|" separators=",">
        <mrow>
          <mi>x</mi>
        </mrow>
      </mfenced>
      <mo>-</mo>
      <mi>&lambda;</mi>
    </mrow>
    <mrow>
      <mn>0</mn>
    </mrow>
  </mfenced>
</mrow>
</math>



</div>
<div style="float:right">
	<p align="right">(9)</p>
</div>
<p style="clear:both"></p>
</div>

<p>where <em>S</em> performs soft-thresholding on each voxel in the image, sending it to zero if it is smaller than the weight <em>&lambda;</em>. Since the spectrum is purely real, <em>C*</em> corresponds to convolution with reversed spectrum, which can be readily implemented using point-by-point multiplication in the Fourier domain. Likewise, <em>C*C</em> is also block circulant and can be implemented by a multiplication in the Fourier domain. It should be noted that the adjoint reconstruction of the projections (<em>R*C*y</em>) does not change, so it is computed only once for speed. The parameter <em>&mu;</em> is related to the maximum eigenvalue of the forward operator (<em>CR</em>), but its value is assigned manually since it depends on the gradient angles and it is not generally known in advance.</p>

<p>After updating the image with soft-thresholding, a non-negativity constraint is imposed because the spin density cannot assume a negative value. The reconstruction continues with the TV denoising algorithm developed by Taboole et al. (<a href="#_ENREF_30">30</a>). We used an isotropic 3D TV computed along the X, Y, and Z axes. An overview of the entire reconstruction is given in Listing 1.</p>

<table border=1>
<tr> <td>

<table>
<tr> <td align=left>
<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>y</mi>
        <mn>1</mn>
  </msub>
  <mo>=</mo>
  <msup>
        <mrow>
          <mi>R</mi><mo>&ApplyFunction;</mo>
        </mrow>
        <mo>*</mo>
  </msup>
  <msup>
        <mrow>
          <mi>C</mi><mo>&ApplyFunction;</mo>
        </mrow>
        <mo>*</mo>
  </msup>
  <mi>y</mi>
</mrow>
</math>


<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>x</mi>
        <mn>0</mn>
  </msub>
  <mo>=</mo>
  <msub>
          <mi>z</mi>
        <mn>0</mn>
  </msub>
  <mo>=</mo>
  <msub>
        <mrow>
          <mfenced open="[" close="]" separators=",">
            <mrow>
              <mn>0</mn>
            </mrow>
          </mfenced>
        </mrow>
      <mrow>
        <mi>N</mi>
        <mo>&times;</mo>
        <mi>N</mi>
        <mo>&times;</mo>
        <mi>N</mi>
      </mrow>
  </msub>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <mi>n</mi>
  <mo>=</mo>
  <mn>0</mn>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>a</mi>
        <mn>0</mn>
  </msub>
  <mo>=</mo>
  <mn>1</mn>
</mrow>
</math>

<b>Repeat</b>
</td></tr>
<tr> <td colspan="20%">
&nbsp;
</td> <td>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>x</mi>
        <mi>n</mi>
  </msub>
  <mo>=</mo>
  <mi>S</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <msub>
              <mi>z</mi>
            <mi>n</mi>
      </msub>
      <mo>-</mo>
      <mi>&mu;</mi>
      <mfenced open="(" close=")" separators=",">
        <mrow>
          <msup>
                <mrow>
                  <mi>R</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <msup>
                <mrow>
                  <mi>C</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <mi>C</mi><mo>&ApplyFunction;</mo>
          <mi>R</mi><mo>&ApplyFunction;</mo>
          <msub>
                  <mi>z</mi>
                <mi>n</mi>
          </msub>
          <mo>-</mo>
          <msup>
                <mrow>
                  <mi>R</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <msup>
                <mrow>
                  <mi>C</mi><mo>&ApplyFunction;</mo>
                </mrow>
                <mo>*</mo>
          </msup>
          <mi>y</mi>
        </mrow>
      </mfenced>
    </mrow>
    <mrow>
      
        <mspace />
      
      <mfrac>
        <mrow>
          <msub>
                  <mi>&lambda;</mi>
                <mn>1</mn>
          </msub>
          <mi>&mu;</mi>
        </mrow>
        <mrow>
          <mn>2</mn>
        </mrow>
      </mfrac>
    </mrow>
  </mfenced>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>x</mi>
        <mi>n</mi>
  </msub>
  <mo>=</mo>
  <mi>max</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <msub>
              <mi>x</mi>
            <mi>n</mi>
      </msub>
    </mrow>
    <mrow>
      <mn>0</mn>
    </mrow>
  </mfenced>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>a</mi>
      <mrow>
        <mi>n</mi>
        <mo>+</mo>
        <mn>1</mn>
      </mrow>
  </msub>
  <mo>=</mo>
  <mfrac>
    <mrow>
      <mn>1</mn>
      <mo>+</mo>
      <msqrt>
        <mn>1</mn>
        <mo>+</mo>
        <msubsup>
                <mi>a</mi>
              <mi>n</mi>
              <mn>2</mn>
        </msubsup>
      </msqrt>
    </mrow>
    <mrow>
      <mn>2</mn>
    </mrow>
  </mfrac>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>u</mi>
        <mi>n</mi>
  </msub>
  <mo>=</mo>
  <msub>
          <mi>x</mi>
        <mi>n</mi>
  </msub>
  <mo>+</mo>
  <mfrac>
    <mrow>
      <msub>
              <mi>a</mi>
            <mi>n</mi>
      </msub>
      <mo>-</mo>
      <mn>1</mn>
    </mrow>
    <mrow>
      <msub>
              <mi>a</mi>
          <mrow>
            <mi>n</mi>
            <mo>+</mo>
            <mn>1</mn>
          </mrow>
      </msub>
    </mrow>
  </mfrac>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <msub>
              <mi>x</mi>
            <mi>n</mi>
      </msub>
      <mo>-</mo>
      <msub>
              <mi>x</mi>
          <mrow>
            <mi>n</mi>
            <mo>-</mo>
            <mn>1</mn>
          </mrow>
      </msub>
    </mrow>
  </mfenced>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  
    <mrow>
      <msub>
      <mi>z</mi>
          <mrow>
            <mi>n</mi>
            <mo>+</mo>
            <mn>1</mn>
          </mrow>
      </msub>
  <mo>=</mo>

  <mi>arg</mi><mo>&ApplyFunction;</mo>

      <munder>
            <mrow>
              <mi>min</mi><mo>&ApplyFunction;</mo>
            </mrow>
            <mi>z</mi>
      </munder>
    </mrow>
  
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>z</mi>
              <mo>-</mo>
      <msub>
              <mi>u</mi>
              <mi>n</mi>
      </msub>
            </mrow>
          </mfenced>
        </mrow>
        <mn>2</mn>
  </msub>
  <mo>+</mo>
  <msub>
          <mi>&lambda;</mi>
        <mn>2</mn>
  </msub>
  <msub>
        <mrow>
          <mfenced open="&parallel;" close="&parallel;" separators=",">
            <mrow>
              <mi>TV</mi><mo>&ApplyFunction;</mo>
              <mfenced open="(" close=")" separators=",">
                <mrow>
                  <mi>z</mi>
                </mrow>
              </mfenced>
            </mrow>
          </mfenced>
        </mrow>
        <mn>1</mn>
  </msub>
</mrow>
</math>

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <mi>n</mi>
  <mo>=</mo>
  <mi>n</mi>
  <mo>+</mo>
  <mn>1</mn>
</mrow>
</math>


</td></tr>
<tr><td>

</td></tr>
</table>

<b>Until</b> z<sub>n</sub> satisfies a stopping criterion.

<math display="block" xmlns="&mathml;" indentalign="left">
<mrow>
  <msub>
          <mi>x</mi>
        <mi>CS</mi>
  </msub>
  <mo>=</mo>
  <msub>
          <mi>z</mi>
        <mi>n</mi>
  </msub>
</mrow>
</math>

</td></tr>
<tr> <td>
Listing 1. Pseudo-code Overview of the CS EPRI Reconstruction
</td></tr>
</table>


<h3>Implementation of a 3D Radon operator and its Exact Adjoint</h3>

<p>The 3D Radon operator and its adjoint were constructed using implicit operators rather than explicit matrix representations. The size of the matrices required to explicitly represent these operators as matrices would have far exceeded computational memory for even modestly-sized 64x64x64 image volumes. To handle this limitation, we adopted a memory efficient implementation of <em>R</em> and <em>R* </em>as described by De Man and Basu (<a href="#_ENREF_31">31</a>,<a href="#_ENREF_32">32</a>). We extended their algorithm to project 3D image volumes to a line using the distance-driven projection and backprojection operators. The distance-driven projection and backprojection operators have the advantages of being fast, accurate, and exact adjoints. Entire subvolumes of the 3D image volume can be projected or backprojected in parallel, and the cache coherence of the algorithm scales well on modern multi-core CPUs. The distance-driven kernel operator was implemented in C for speed, and the remaining functions in the reconstruction were implemented in Matlab for simplicity. The L2 of the projections were normalized to unity before reconstruction to narrow the range of <em>&lambda;</em>1 and <em>&lambda;</em>2 between datasets which had diverse spectral amplitudes.</p>

<h2>METHODS</h2>

<h3>Simulations</h3>

<p>Simulations were performed to measure sampling incoherence and sparsity in EPRI. While EPRI cannot achieve truly incoherent sampling because data are collected in the form of projections, there may still be differences in incoherence from choosing different gradient angles. The maximum amplitude of the sidelobe-to-peak ratio in the point spread function (PSF) was used as a measurement of the sampling incoherence (<a href="#_ENREF_22">22</a>). A noiseless simulation of the PSF of <em>R</em> was computed by projecting and backprojecting an impulse function in the image domain (Figure 1). The simulation was performed for 100 projections from both the Equal Linear Angle (ELA) sampling strategy and the 3D Golden Means (GM) sampling strategy (<a href="#_ENREF_33">33</a>).</p>

<a id="Fig1"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig01.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 1.</span> Point spread functions (PSF) along X, Y, and Z axes for different sampling strategies (a-c). The GM PSF approaches zero rapidly along every axis, whereas the sidelobes of ELA are bigger and wider. The maximum of the sidelobe-to-peak ratio for GM and ELA are 0.218 and 0.241, respectively,&nbsp; indicating that GM sampling has more incoherence than ELA sampling. Individual 2D slices of the 3D PSFs (d) show ELA&#39;s PSF in the Z plane has strong sidelobes.</p>
</div></a>

<p>The sparsity of EPR images under Eq (4) was examined using a synthetic phantom similar to physical phantoms used in previous EPRI publications (<a href="#_ENREF_1">1</a>). A noiseless 3D simulation of ellipsoids in the shape of the letters &quot;EPR&quot; was fed through a simulated acquisition using the forward model (<em>RC</em>), and then the CS reconstruction was performed to examine the effects of ELA and GM sampling (Figure 2). The simulation was performed using a first derivative Lorenztian lineshape generated by the Robinson-Mailer model (<a href="#_ENREF_34">34</a>) with a HWHM linewidth of 0.01 mT, 0.04 mT modulation amplitude, 2 mT sweep width, 500 projections from either ELA or GM, 25 mT/m gradient amplitude, and 30 mm field of view. The CS reconstruction was performed with <em>&lambda;</em>1 = 0.01, <em>&lambda;</em>2 = 0.005, and <em>&mu;</em> = 0.4. The algorithm was terminated when there was at most a 0.1% change in the l1-norm of the image for two successive iterations. The normalized mean-squared error (NMSE) was computed relative to the original unblurred phantom.</p>

<a id="Fig2"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig02.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 2.</span> Compressed Sensing (CS) reconstructions of a 3D phantom with different sampling strategies. Projections (N=625) were simulated with EPR first-derivative Lorentzian lineshape blurring to investigate sampling incoherence and sparsity in EPRI. The normalized mean-squared error (NMSE) is indicated in the above each slice. The spatial resolution and reconstruction accuracy is improved in GM as compared to ELA sampling due to the greater sampling incoherence in GM sampling.</p>
</div></a>

<h3>Phantom Experiments</h3>

<p>To empirically determine how much acceleration can be applied to EPR acquisitions with real noise, a phantom consisting of 19 tubes (43 mm long, 4.0 mm outer diameter, 3.81 mm inner diameter) of 1 mM tetrathiatriarylmethyl radical (TAM) were imaged on a 1.2 GHz EPR imaging system. The approximate linewidth was 0.01 mT, and the acquisition parameters were 0.012 mT modulation amplitude, 100 kHz modulation frequency, 3 mT sweep width, 43.3 mT center field, 5.24 s per projection, 1,764 projections, 26.7 mT/m gradient amplitude, as previously reported (<a href="#_ENREF_35">35</a>). The dataset was retrospectively downsampled by reducing the number of projections while maintaining an approximately uniform distribution. Images were reconstructed with both CS and FBP for comparison of the two reconstruction methods.</p>

<p>To quantify the accuracy of the reconstructions, the sizes and positions of the tubes were measured in the full dataset by least-squares fitting of the center image slice using 2D Gaussian functions. The average of the Full-Width, Half-Maximum (FWHM) of each Gaussian was compared between the CS and FBP reconstructions. The physical dimensions of the tubes were measured using a dial caliper with 0.02 mm accuracy. The physical inner diameter of the tube was compared to the FWHM of the Gaussians, and the physical outer diameter of the tube was compared to the spacing in-between the centers of the Gaussians.</p>

<h3>Isolated Rat Heart Imaging</h3>

<p>Ex vivo rat heart experiments were performed on the same imaging system to determine the effectiveness of the CS reconstruction with biologically limited SNR. Lithium octa-n-butoxynaphthalocyanine (LiNc-BuO) suspension was infused into an isolated rat heart, and then the heart was subjected to global ischemia. The linewidth of the probe narrowed to 0.01 mT before the image acquisition began (<a href="#_ENREF_36">36</a>). Projections (N=256) from ELA were acquired in 697 s with 0.02 mT modulation amplitude, 1.0 mT sweep width, 40 mT/m gradient amplitude, and 25 mm field of view. To examine the effects of different sparsifying transforms, the CS reconstruction was performed with different reconstruction weights. The dataset was reconstructed with &lambda;1 = &lambda;2 = 0 (equivalent to ART), and then reconstructed again with <em>&lambda;</em>1 = 2 and <em>&lambda;</em>2 = 0.02 (both penalties). In both cases, the images were reconstructed on an 80x80x80 volume with &mu; = 0.5. &nbsp;&nbsp;</p>

<p>A second isolated rat heart was perfused with LiNc-BuO, and 1,024 projections were acquired with GM sampling in 266 s. A linewidth of 0.01 mT was measured. The imaging acquisition consisted of 0.04 mT modulation amplitude, 1.4 mT sweep width, 47 mT/m gradient amplitude, and 30 mm field of view. Subsets of the projections were reconstructed to determine the minimum amount of data needed to reconstruct a high quality image. The acceleration factor was defined as the fraction of projections retained from the original 1,024 projections (e.g., an acceleration factor of 4 corresponded to using only the first 256 projections to perform the reconstruction). FBP reconstructions were performed on the same subsets. The peak SNR was calculated in each reconstructed image by dividing the maximum amplitude of the image by the standard deviation of the non-signal regions of the image. The non-signal regions were determined by thresholding the FBP reconstruction from the full dataset, and this mask was applied to all subsequent calculations. The CS reconstruction was performed with &lambda;1 = 0.5, &lambda;2 = 0.005, and &mu; = 1.</p>

<h3>High Resolution In Vivo Mouse GI Tract Imaging</h3>

<p>To examine the effects of the CS reconstruction on spatial resolution, a high resolution gastro-intestinal imaging experiment was performed by feeding mice a mixture of activated charcoal and glucose, as previously described (<a href="#_ENREF_37">37</a>). Projections (N=1,024) from ELA were acquired in 91 min with a linewidth of 0.1 mT, 0.14 mT modulation amplitude, 6.0 mT sweep width, 150 mT/m gradient amplitude, and 40 mm field of view. The CS reconstruction was performed with &lambda;1 = 0.5, &lambda;2 = 0.02, and &mu; = 1.</p>

<h3>Image Sharpness Index</h3>

<p>To quantify the sharpness of edges in the GI tract and heart images, the image sharpness index method was employed (<a href="#_ENREF_38">38</a>). A sigmoid function (L) given by</p>


<div class="figure" style="border:none">
<div style="float:left">

<math display="block" xmlns="&mathml;">
<mrow>
  <mi>L</mi><mo>&ApplyFunction;</mo>
  <mfenced open="(" close=")" separators=",">
    <mrow>
      <mi>x</mi>
    </mrow>
  </mfenced>
  <mo>=</mo>
  <msub>
          <mi>I</mi>
        <mn>0</mn>
  </msub>
  <mo>+</mo>
  <mfrac>
    <mrow>
      <msub>
              <mi>I</mi>
            <mn>1</mn>
      </msub>
    </mrow>
    <mrow>
      <mn>1</mn>
      <mo>+</mo>
      <msup>
              <mn>10</mn>
          <mrow>
            <mo>-</mo>
            <mi>w</mi>
            <mfenced open="(" close=")" separators=",">
              <mrow>
                <mi>x</mi>
                <mo>-</mo>
                <msub>
                        <mi>x</mi>
                      <mn>0</mn>
                </msub>
              </mrow>
            </mfenced>
          </mrow>
      </msup>
    </mrow>
  </mfrac>
</mrow>
</math>


</div>
<div style="float:right">
	<p align="right">(10)</p>
</div>
<p style="clear:both"></p>
</div>


<p>was fitted along the normalized position (<em>x</em>) in 1-dimensional line profiles orthogonal to image edges using a least-squares fit. The fitted parameters of the model consisted of an offset intensity (<em>I</em>0), an intensity amplitude (<em>I</em>1), a center offset (<em>x</em>0), and a sigmoid width (<em>w</em>). Larger values of <em>w</em> corresponded to sharper edges. The mean and standard deviation of the <em>w</em> in all edges in each image were computed, reported as image sharpness index (ISI), and compared using a Student t-test.</p>

<h2>RESULTS</h2>

<h3>Simulations</h3>

<p>Incoherent sampling in EPRI was examined by comparing the point spread function (PSF) resulting from the ELA and GM sampling strategies (<a href="#Fig1">Figure 1</a>). Individual line profiles along the X, Y, and Z axes show that the GM sampling is more incoherent than ELA sampling due to the smaller sidelobes. The maximum of the sidelobe-to-peak ratio for GM and ELA are 0.218 and 0.241, respectively, indicating that GM sampling has more incoherence than ELA sampling. The PSF of GM sampling also goes to zero much more rapidly than ELA sampling. Both distributions have the same center peak width, which is dominated by the linewidth of the Lorentzian distribution used in the simulation.</p>

<p>The effects of incoherent sampling were demonstrated in a noiseless 3D simulation of ellipsoids in the shape of the letters &quot;EPR&quot; (<a href="#Fig2">Figure 2</a>). As the phantom was entirely synthetic and noiseless, the artifacts observed in the reconstructions are entirely due to differences in the ELA and GM sampling strategies which serves as a proxy for incoherence. The same CS reconstruction parameters were used for both simulations.&nbsp; Slices from the ELA reconstruction showed strong blurring and streaking along the X and Y axes. Artifacts from the GM reconstruction were smaller and isotropic. The NMSE was approximately 25% lower in the GM reconstruction as compared to the ELA reconstruction.</p>

<h3>Phantom Experiments</h3>

<p>FBP and CS reconstructions were compared in the 19 tube TAM phantom (Figure 3). The original 1,764 projections were retrospectively accelerated by the acceleration factors of 2, 4, 9, and 18 corresponding to 882, 441, 196, and 98 projections, respectively. The CS images show little visual degradation at 9-fold acceleration, whereas the FBP images have decreasing SNR and increasing streaking artifacts due to angular undersampling.</p>

<a id="Fig3"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig03.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 3.</span> FBP and CS reconstructions of the 19 tube TAM phantom. The original 1,764 projections were retrospectively accelerated by the factors indicated above to 882, 441, 196, and 98 projections, respectively. The CS images show little degradation at 9-fold acceleration, whereas the FBP images have rapidly decreasing SNR and increasing streaking artifacts due to angular undersampling.</p>
</div></a>

<p>After fitting the center image slice with 2D Gaussian functions, the FWHM of the CS images was 3.89 &plusmn; 0.06 mm (mean &plusmn; standard deviation) with a spacing of 5.98 &plusmn; 0.09 mm. The FWHM of the FBP images was 4.20 &plusmn; 0.07 mm with a spacing of 5.95 &plusmn; 0.10 mm. The caliper measurements indicated a 3.81 mm inner diameter and a 5.97 mm outer diameter. The spacings between Gaussians of both CS and FBP reconstructions matched the physical outer diameter within one standard deviation, but the FWHM of the FBP Gaussian was bigger than the physical inner diameter by 0.39 mm (10%). In contrast, the CS FWHM was within 0.09 mm of the true inner diameter (2%).</p>

<h3>Isolated Rat Heart Imaging</h3>

<p>The effects of regularization on the CS reconstruction were demonstrated in a LiPc rat heart dataset (Figure 4). In the absence of any regularization, some streaking artifacts and high frequency noise appeared in the reconstructed images (4-a). When using both the l1 and TV penalty terms, the image SNR increased from 11.6 &plusmn; 3.8 to 21.8 &plusmn; 7.7 and background artifacts were decreased (4-b).</p>

<a id="Fig4"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig04.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 4.</span> Effects of regularization using a LiNc-BuO rat heart dataset. In the absence of any regularization, the reconstruction is equivalent to ART with lineshape information (a). When using both the l <em>1</em> and TV penalty terms, the image has increased SNR and decreased artifacts (b).</p>
</div></a>

<p>Acceleration of the acquisition was compared by retrospectively reconstructing only a small fraction of the projections originally acquired in a LiNc-BuO rat heart dataset (Figure 5). The FBP reconstruction (top row) degraded as the acceleration factor increased from 2 (i.e., using 512 out of the 1,024 original projections) to 32 (using only 32 projections). In contrast, the CS reconstruction (bottom row) also degraded, but the 8-fold acceleration was visually similar to the fully sampled image. The ISI for the FBP reconstruction from the full 1,024 projections was 0.56&plusmn;0.02 (mean &plusmn; standard deviation), which was not different (P&gt;0.25) than any of the other FBP reconstructions up to an acceleration factor of 16X. In contrast, the ISI for the CS reconstruction with the full 1,024 projections was 0.88&plusmn;0.25, which was significantly different (P&lt;0.01) than the FBP reconstructions. There was no significant difference in ISI between CS reconstructions with an acceleration factor of 16X or less. We repeated the CS reconstructions after dividing both reconstruction weights &lambda;1 and &lambda;2 by 10, and the conclusions did not change. &nbsp;&nbsp;</p>

<a id="Fig5"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig05.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 5.</span> Comparison of Compressed Sensing (CS) and Filtered Backprojection (FBP) reconstructions in a LiNc-BuO heart dataset. As the acceleration factor increases, the visual quality of both algorithms degrade. Both algorithms fail at 32-fold acceleration.</p>
</div></a>

<p>The effects of acceleration on SNR were examined in the LiNc-BuO rat heart dataset on a log-log plot (Figure 6). The predicted square root of time reduction in SNR was similar in both the FBP and CS reconstructions, though the CS reconstruction started with higher SNR and ISI. When the CS reconstruction was used, the SNR dropped from 70.9 (fully sampled) to 11.6 (8-fold acceleration). In comparison, the FBP reconstruction dropped from 12.9 to 2.8 (fully sampled vs. 16-fold).</p>

<a id="Fig6"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig06.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 6.</span> SNR in 3D reconstructed heart images vs. acceleration factor on a log-log scale. Increasing the acceleration factor degrades both reconstructions. Least squares fits of SNR vs. acceleration factor indicate a slightly faster degradation of the CS reconstruction, but the CS reconstruction starts at a higher SNR.</p>
</div></a>

<h3>In Vivo Mouse GI Tract Imaging</h3>

<p>The effects of deconvolution were examined by comparing the FBP and CS reconstructions of activated charcoal in the GI tract of a mouse (Figure 7). The spatial resolution of the FBP reconstruction is limited by explicit deconvolution, which results in blurring and negative values in the image. The resolution in the CS reconstruction is limited only by the original projections and the linewidth of the char. The SNR improved from 10.6 &plusmn; 3.1 to 20.7 &plusmn; 6.1 in the FBP and CS reconstructions, respectively. The ISI for the FBP reconstruction was 0.56&plusmn;0.05, which was significantly different (P&lt;0.001) than the 1.13&plusmn;0.66 ISI for the CS reconstruction.</p>

<a id="Fig7"><div class="figure" >
<div class="subfigure" >
	<img src="images/cs-fig07.gif" width="650px" />
</div>
<p class="figureCaption"><span class="figureName">Figure 7.</span> EPR imaging of GI tract from a mouse fed charcoal EPR probe. CS improves the spatial resolution because convolution with the EPR spectrum is included in the forward model, whereas FBP must use explicit deconvolution. The boundaries of the GI tract are sharpened by the l <em>1</em> prior. The SNR was doubled. Arrows indicate &ldquo;spike&rdquo; artifacts removed by the CS reconstruction.</p>
</div></a>

<h2>DISCUSSION</h2>

<p>A novel CS reconstruction algorithm for 3D spatial EPR imaging was developed and evaluated in simulations, phantoms, and murine imaging models of cardiac and intestinal anatomy. Both penalty terms were necessary to sparsify EPR images and produce robust, high SNR images given the constraints of typical EPRI linewidths and undersampling. The incoherence of sampling strategies was characterized by the PSF and by simulations. The FBP reconstruction was inferior to the CS reconstruction in terms of SNR. An 8-fold acceleration was possible in the cardiac images with no visual loss of quality, and SNR was doubled in gastro-intestinal tract images. Background signals were very effectively suppressed in the animal experiments. Image sharpness index was approximately doubled in both cardiac and gastro-intestinal EPR images by the CS reconstruction as compared to the FBP reconstruction.</p>

<p>Compressed sensing has not been applied to EPRI before in the form proposed here. An earlier study applied parametric modeling to reconstruct 1D spatial, 1D spectral profiles, but 3D reconstructions were deemed too large to solve (<a href="#_ENREF_17">17</a>). The use of the TV operator is an advantage unexplored by previous applications of CS to EPRI. The TV operator removes oscillations and other background signals from the reconstructed images, which makes the CS reconstruction less sensitive to noise. This effect is visually apparent in the GI tract images where &ldquo;spike&rdquo; artifacts in the FBP reconstructions are removed in the CS reconstructions (Fig 7, arrows).&nbsp; Previous reconstruction algorithms have tried to improve the spatial resolution of EPRI by improving the deconvolution algorithm or by incorporating the lineshape information into the reconstruction with varying degrees of success&nbsp; (<a href="#_ENREF_39">39</a>). In contrast, this method avoids explicit deconvolution entirely. Instead, the lineshape information is seamlessly incorporated directly into the forward model, which avoids choosing a cut-off frequency that reduces SNR for improved spatial resolution. Signals that extend beyond the field segment collected (i.e., due to hyperfine splitting, or intentionally truncated to reduce acquisition time) can also be incorporated into the forward model. Specifically, the operators C and C* are implemented by the same functions when hyperfine splitting occurs in the EPR spectrum. The phantom experiments indicated that the spatial resolution is better in the CS reconstruction than the FBP reconstruction when the physical dimensions of the tubes are assumed to be known.</p>

<p>There are several complimentary approaches available to expediting the EPR acquisition. If only a small region of the anatomy contains a EPR signal of interest, then the magnetic field sweep width can be tailored to cover only that region, resulting in a corresponding reduction in acquisition time (<a href="#_ENREF_40">40</a>,<a href="#_ENREF_41">41</a>). If a dynamic EPR signal is being investigated for probe kinetics, principal components analysis can be applied to the temporal signal evolution to suppress noise (<a href="#_ENREF_42">42</a>). These approaches can be combined with the CS method developed here to exploit the signal sparsity and further accelerate the EPR acquisition. Time domain EPR is already taking advantage of CS reconstructions to great effect (<a href="#_ENREF_43">43</a>,<a href="#_ENREF_44">44</a>).&nbsp;&nbsp;&nbsp;</p>

<p>The choice of gradient angles is important (<a href="#_ENREF_45">45</a>). For static EPR imaging with the CS reconstruction, GM sampling is recommended over other sampling strategies. Traditional sampling strategies like ELA can be used with the CS reconstruction, but a loss of efficiency occurs, and spatial resolution is compromised even in the absence of noise. The GM datasets in this work were much easier to accelerate (i.e., retrospectively downsample) because subsets of projections maintain the same approximate uniformity due to the recursive nature of the golden ratio.</p>

<p>There are some limitations of the new reconstruction. Choosing the reconstruction weights &lambda;1 and &lambda;2 is difficult to do systematically. L curve methods can be used for picking a single reconstruction weight (<a href="#_ENREF_46">46</a>), but their generalization to multiple weights remains an open research topic&nbsp; (<a href="#_ENREF_47">47</a>). A complete and rigorous evaluation of different choices of these values is outside the scope of this preliminary study. Normalizing the l2 of the projections to unity made the values of &lambda;1 and &lambda;2 more consistent between datasets. Another consideration is the additional computational time required for the reconstruction, which was approximately six minutes for the CS images shown in Figure 7 (bottom row) but less than one minute for FBP (top row). Computational power continues to improve, and the distance-driven Radon transform can be implemented using graphics card computation for additional speed (<a href="#_ENREF_31">31</a>). A further reduction in reconstruction time can be achieved using the Fourier transform to compute the Gram operators (<em>R*C*CR</em>) in Eq (8) with Toeplitz embedding (<a href="#_ENREF_48">48</a>).&nbsp;</p>

<p>Probes with multiple peaks in the EPR spectrum (e.g., nitroxides) can be used in the same forward model developed here. Some spatial resolution will be lost to the broader linewidths, but it may be possible to reconstruct images from even fewer projections. Accelerating the EPR acquisition further is possible, especially for EPRI experiments that repeatedly acquire the same image to capture the kinetics of redox metabolism. The method proposed here can also be extended to spectral-spatial EPRI by introducing a sparsifying transform for the EPR spectrum, enabling rapid measurements of pH, oxygen, etc. Instead of acquiring individual projections with fast-scan, the spinning gradient acquisition can provide nearly limitless projections very quickly. Recent work has shown how to make the sampling strategy in the spinning gradient acquisition both uniform and efficient (<a href="#_ENREF_36">36</a>). Future work could combine a CS reconstruction with the uniform spinning gradient acquisition to produce fast, high quality spectral-spatial images.</p>

<h2>CONCLUSION</h2>

<p>Compressed sensing has been applied to accelerate and improve spatial EPRI with diffuse probes for the first time. This approach exploits the structure present in EPR images via l1 regularized least-squares. Leveraging efficient implementation of forward operators and their exact adjoints as well as fast optimization routines allows reconstructing large EPR images in a reasonable time. Both simulation and in vivo data indicate that CS-based reconstruction allows reconstructing high fidelity EPR images from highly undersampled data. The resulting images also exhibit high spatial resolution and are devoid of artifacts.</p>

<h2>REFERENCES</h2>

<p class="refCited"><a name="_ENREF_1">1. Eaton GR, Eaton SS, Ohno K, editors. EPR Imaging and In Vivo EPR. 1st ed. Boca Raton, FL: CRC Press; 1991. 321 p.</a></p>

<p class="refCited"><a name="_ENREF_2">2. Williams BB, Halpern H. In vivo EPR Imaging. In: Eaton SS, Eaton GR, Berliner LJ, editors. Biomedical EPR, Part A: Free Radicals, Metals, Medicine, and Physiology New York: Kluwer Academic; 2005. p 283-319.</a></p>

<p class="refCited"><a name="_ENREF_3">3. Elas M, Bell R, Hleihel D, Barth ED, McFaul C, Haney CR, Bielanska J, Pustelny K, Ahn KH, Pelizzari CA, Kocherginsky M, Halpern HJ. Electron paramagnetic resonance oxygen image hypoxic fraction plus radiation dose strongly correlates with tumor cure in FSa fibrosarcomas. International journal of radiation oncology, biology, physics 2008;71(2):542-549. PMID: 18474313. PMC: 2577780.</a></p>

<p class="refCited"><a name="_ENREF_4">4. Halpern HJ, Yu C, Peric M, Barth E, Grdina DJ, Teicher BA. Oxymetry deep in tissues with low-frequency electron paramagnetic resonance. Proc Natl Acad Sci U S A 1994;91(26):13047-13051. PMID: 7809170. PMC: 45578.</a></p>

<p class="refCited"><a name="_ENREF_5">5. Matsumoto S, Hyodo F, Subramanian S, Devasahayam N, Munasinghe J, Hyodo E, Gadisetti C, Cook JA, Mitchell JB, Krishna MC. Low-field paramagnetic resonance imaging of tumor oxygenation and glycolytic activity in mice. The Journal of clinical investigation 2008;118(5):1965-1973. PMID: 18431513. PMC: 2323191.</a></p>

<p class="refCited"><a name="_ENREF_6">6. Khramtsov VV, Grigor&#39;ev IA, Foster MA, Lurie DJ, Nicholson I. Biological applications of spin pH probes. Cellular and molecular biology 2000;46(8):1361-1374. PMID: 11156481. </a></p>

<p class="refCited"><a name="_ENREF_7">7. Redler G, Barth ED, Bauer KS, Jr., Kao JP, Rosen GM, Halpern HJ. In vivo electron paramagnetic resonance imaging of differential tumor targeting using cis-3,4-di(acetoxymethoxycarbonyl)-2,2,5,5-tetramethyl-1-pyrrolidinyloxyl. Magn Reson Med 2013. PMID: 23776127. </a></p>

<p class="refCited"><a name="_ENREF_8">8. Velayutham M, Li H, Kuppusamy P, Zweier JL. Mapping ischemic risk region and necrosis in the isolated heart using EPR imaging. Magn Reson Med 2003;49(6):1181-1187. PMID: 12768597. </a></p>

<p class="refCited"><a name="_ENREF_9">9. Ueda A, Yokoyama H, Nagase S, Hirayama A, Koyama A, Ohya H, Kamada H. In vivo temporal EPR imaging for estimating the kinetics of a nitroxide radical in the renal parenchyma and pelvis in rats. Magn Reson Imaging 2002;20(1):77-82. PMID: 11973032. </a></p>

<p class="refCited"><a name="_ENREF_10">10. Kuppusamy P, Li H, Ilangovan G, Cardounel AJ, Zweier JL, Yamada K, Krishna MC, Mitchell JB. Noninvasive imaging of tumor redox status and its modification by tissue glutathione levels. Cancer research 2002;62(1):307-312. PMID: 11782393. </a></p>

<p class="refCited"><a name="_ENREF_11">11. Swartz HM, Khan N, Khramtsov VV. Use of electron paramagnetic resonance spectroscopy to evaluate the redox state in vivo. Antioxidants &amp; redox signaling 2007;9(10):1757-1771. PMID: 17678441. PMC: 2702846.</a></p>

<p class="refCited"><a name="_ENREF_12">12. Mikuni T, He G, Petryakov S, Fallouh MM, Deng Y, Ishihara R, Kuppusamy P, Tatsuta M, Zweier JL. In vivo detection of gastric cancer in rats by electron paramagnetic resonance imaging. Cancer research 2004;64(18):6495-6502. PMID: 15374960. </a></p>

<p class="refCited"><a name="_ENREF_13">13. Elas M, Ichikawa K, Halpern HJ. Oxidative stress imaging in live animals with techniques based on electron paramagnetic resonance. Radiation research 2012;177(4):514-523. PMID: 22348251. PMC: 3708477.</a></p>

<p class="refCited"><a name="_ENREF_14">14. Ahmad R, Deng Y, Vikram DS, Clymer B, Srinivasan P, Zweier JL, Kuppusamy P. Quasi Monte Carlo-based isotropic distribution of gradient directions for improved reconstruction quality of 3D EPR imaging. J Magn Reson 2007;184(2):236-245. PMID: 17095271. PMC: 1892230.</a></p>

<p class="refCited"><a name="_ENREF_15">15. Liu Y, Song Y, De Pascali F, Liu X, Villamena FA, Zweier JL. Tetrathiatriarylmethyl radical with a single aromatic Hydrogen as a highly sensitive and specific superoxide probe. Free Radic Biol Med 2012;53(11):2081-2091. PMID: 23000244. </a></p>

<p class="refCited"><a name="_ENREF_16">16. Subramanian S, Koscielniak JW, Devasahayam N, Pursley RH, Pohida TJ, Krishna MC. A new strategy for fast radiofrequency CW EPR imaging: direct detection with rapid scan and rotating gradients. J Magn Reson 2007;186(2):212-219. PMID: 17350865. PMC: 2084379.</a></p>

<p class="refCited"><a name="_ENREF_17">17. Tseitlin M, Czechowski T, Eaton SS, Eaton GR. Regularized optimization (RO) reconstruction for oximetric EPR imaging. J Magn Reson 2008;194(2):212-221. PMID: 18667346. PMC: 3419263.</a></p>

<p class="refCited"><a name="_ENREF_18">18. Tseitlin M, Dhami A, Eaton SS, Eaton GR. Comparison of maximum entropy and filtered back-projection methods to reconstruct rapid-scan EPR images. J Magn Reson 2007;184(1):157-168. PMID: 17070083. PMC: 2744395.</a></p>

<p class="refCited"><a name="_ENREF_19">19. Johnson CA, McGarry D, Cook JA, Devasahayam N, Mitchell JB, Subramanian S, Krishna MC. Maximum entropy reconstruction methods in electron paramagnetic resonance imaging. Annals of Operations Research 2003;119(1-4):101-118. </a></p>

<p class="refCited"><a name="_ENREF_20">20. Grinberg OY, Smirnov AI, Swartz HM. High spatial resolution multi-site EPR oximetry. The use of convolution-based fitting method. J Magn Reson 2001;152(2):247-258. PMID: 11567578. </a></p>

<p class="refCited"><a name="_ENREF_21">21. Som S, Potter LC, Ahmad R, Vikram DS, Kuppusamy P. EPR oximetry in three spatial dimensions using sparse spin distribution. J Magn Reson 2008;193(2):210-217. PMID: 18538600. PMC: 2630719.</a></p>

<p class="refCited"><a name="_ENREF_22">22. Lustig M, Donoho D, Pauly JM. Sparse MRI: The application of compressed sensing for rapid MR imaging. Magn Reson Med 2007;58(6):1182-1195. PMID: 17969013. </a></p>

<p class="refCited"><a name="_ENREF_23">23. Donoho D. Compressed sensing. IEEE Transactions on Information Theory 2006;52(4):1289-1306. </a></p>

<p class="refCited"><a name="_ENREF_24">24. Choi K, Wang J, Zhu L, Suh TS, Boyd S, Xing L. Compressed sensing based cone-beam computed tomography reconstruction with a first-order method. Med Phys 2010;37(9):5113-5125. PMID: 20964231. PMC: 2945747.</a></p>

<p class="refCited"><a name="_ENREF_25">25. Lustig M, Donoho DL, Santos JM, Pauly JM. Compressed Sensing MRI. Signal Processing Magazine, IEEE 2008;25(2):72. PMID: ieee4472246. </a></p>

<p class="refCited"><a name="_ENREF_26">26. Ahmad R, Som S, Johnson DH, Zweier JL, Kuppusamy P, Potter LC. Multisite EPR oximetry from multiple quadrature harmonics. J Magn Reson 2012;214(1):135-143. PMID: 22154283. PMC: 3257390.</a></p>

<p class="refCited"><a name="_ENREF_27">27. Som S, Potter LC, Ahmad R, Kuppusamy P. A parametric approach to spectral-spatial EPR imaging. J Magn Reson 2007;186(1):1-10. PMID: 17276111. PMC: 2020527.</a></p>

<p class="refCited"><a name="_ENREF_28">28. Ahmad R, Clymer B, Vikram DS, Deng Y, Hirata H, Zweier JL, Kuppusamy P. Enhanced resolution for EPR imaging by two-step deblurring. J Magn Reson 2007;184(2):246-257. PMID: 17113800. PMC: 1866261.</a></p>

<p class="refCited"><a name="_ENREF_29">29. Beck A, Teboulle M. A Fast Iterative Shrinkage-Thresholding Algorithm for Linear Inverse Problems. SIAM J Img Sci 2009;2(1):183-202. </a></p>

<p class="refCited"><a name="_ENREF_30">30. Beck A, Teboulle M. Fast gradient-based algorithms for constrained total variation image denoising and deblurring problems. IEEE Trans Image Process 2009;18(11):2419-2434. PMID: 19635705. </a></p>

<p class="refCited"><a name="_ENREF_31">31. Basu S, De Man B. Branchless distance driven projection and backprojection. In: Bouman CA, Miller EL, Pollak I, editors. SPIE Computational imaging IV; 2006; San Jose, CA, USA SPIE The International Society for Optical Engineering. p 1-15. (SPIE Computational imaging IV).</a></p>

<p class="refCited"><a name="_ENREF_32">32. De Man B, Basu S. Distance-driven projection and backprojection in three dimensions. Phys Med Biol 2004;49(11):2463-2475. PMID: 15248590. </a></p>

<p class="refCited"><a name="_ENREF_33">33. Chan RW, Ramsay EA, Cunningham CH, Plewes DB. Temporal stability of adaptive 3D radial MRI using multidimensional golden means. Magn Reson Med 2009;61(2):354-363. PMID: 19165897. </a></p>

<p class="refCited"><a name="_ENREF_34">34. Robinson BH, Mailer C, Reese AW. Linewidth analysis of spin labels in liquids. I. Theory and data analysis. J Magn Reson 1999;138(2):199-209. PMID: 10341123. </a></p>

<p class="refCited"><a name="_ENREF_35">35. Petryakov S, Samouilov A, Kesselring E, Wasowicz T, Caia GL, Zweier JL. Single loop multi-gap resonator for whole body EPR imaging of mice at 1.2 GHz. J Magn Reson 2007;188(1):68-73. PMID: 17625940. PMC: 2714052.</a></p>

<p class="refCited"><a name="_ENREF_36">36. Johnson D, Ahmad R, Liu Y, Chen Z, Samouilov A, Zweier JL. Uniform Spinning Sampling Gradient Electron Paramagnetic Resonance Imaging. Magn Reson Med (in press) 2013 Mar. doi: 10.1002/mrm.24712. . PMID: 23475830. </a></p>

<p class="refCited"><a name="_ENREF_37">37. He G, Shankar RA, Chzhan M, Samouilov A, Kuppusamy P, Zweier JL. Noninvasive measurement of anatomic structure and intraluminal oxygenation in the gastrointestinal tract of living mice with spatial and spectral EPR imaging. Proc Natl Acad Sci U S A 1999;96(8):4586-4591. PMID: 10200306. </a></p>

<p class="refCited"><a name="_ENREF_38">38. Xu J, Napel S, Greenspan H, Beaulieu CF, Agrawal N, Rubin D. Quantifying the margin sharpness of lesions on radiological images for content-based image retrieval. Med Phys 2012;39(9):5405-5418. PMID: 22957608. PMC: 3432101.</a></p>

<p class="refCited"><a name="_ENREF_39">39. Ikebata Y, Sato-Akaba H, Aoyama T, Fujii H, Itoh K, Hirata H. Resolution-recovery for EPR imaging of free radical molecules in mice. Magn Reson Med 2009;62(3):788-795. PMID: 19623620. </a></p>

<p class="refCited"><a name="_ENREF_40">40. Pan X, Xia D, Halpern H. Targeted-ROI imaging in electron paramagnetic resonance imaging. J Magn Reson 2007;187(1):66-77. PMID: 17451981. </a></p>

<p class="refCited"><a name="_ENREF_41">41. Ahn KH, Halpern HJ. Object dependent sweep width reduction with spectral-spatial EPR imaging. J Magn Reson 2007;186(1):105-111. PMID: 17321174. PMC: 2100385.</a></p>

<p class="refCited"><a name="_ENREF_42">42. Redler G, Epel B, Halpern HJ. Principal component analysis enhances SNR for dynamic electron paramagnetic resonance oxygen imaging of cycling hypoxia in vivo. Magn Reson Med 2013. PMID: 23401214. </a></p>

<p class="refCited"><a name="_ENREF_43">43. Devasahayam N, Subramanian S, Murugesan R, Hyodo F, Matsumoto K, Mitchell JB, Krishna MC. Strategies for improved temporal and spectral resolution in in vivo oximetric imaging using time-domain EPR. Magn Reson Med 2007;57(4):776-783. PMID: 17390350. </a></p>

<p class="refCited"><a name="_ENREF_44">44. Subramanian S, Chandramouli GV, McMillan A, Gullapalli RP, Devasahayam N, Mitchell JB, Matsumoto S, Krishna MC. Evaluation of partial k-space strategies to speed up time-domain EPR imaging. Magn Reson Med 2012. PMID: 23045171. PMC: 3548084.</a></p>

<p class="refCited"><a name="_ENREF_45">45. Chan RW, Ramsay EA, Cheung EY, Plewes DB. The influence of radial undersampling schemes on compressed sensing reconstruction in breast MRI. Magn Reson Med 2012;67(2):363-377. PMID: 21656558. </a></p>

<p class="refCited"><a name="_ENREF_46">46. Hansen PC. Analysis of discrete ill-posed problems by means of the L-curve. SIAM Review 1992;34(4):561-580. </a></p>

<p class="refCited"><a name="_ENREF_47">47. Hansen PC. Getting Serious: Choosing the Regularization Parameter. In: Hansen PC, editor. Discrete Inverse Problems: Insight and Algorithms. Philadelphia, PA: Society for Industrial and Applied Mathematics; 2010. p 85-107.</a></p>

<p class="refCited"><a name="_ENREF_48">48. Ahmad R, Austin CD, Potter LC. Toeplitz embedding for fast iterative regularized imaging. Algorithms for Synthetic Aperture Radar Imagery XVIII; 2011 May 12; Orlando, FL, USA. SPIE. p 80510E. (Algorithms for Synthetic Aperture Radar Imagery XVIII).</a></p>

<h2>ACKNOWLEDGEMENTS</h2>

<p>The first author was supported by NIH training grant F32 EB012932. This work was also supported in part by NIH grants EB016096, EB0890 and EB4900.</p>


</div>
</div>

<!-- Google Analytics -->
<?php include_once("analyticstracking.php") ?>

</body></html>