#ifndef __itkIntermodesThresholdImageFilter_h
#define __itkIntermodesThresholdImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkFixedArray.h"

namespace itk {

/** \class IntermodesThresholdImageFilter 
 * \brief Threshold an image using the Intermodes Threshold
 * 
 * Also has the option of taking the minimum between the peaks.
 *
 * See IntermodesThresholdImageCalculator for details and code heritagge
 *
 * \sa IntermodesThresholdImageCalculator
 * \sa BinaryThresholdImageFilter 
 * \sa OtsuThresholdImageFilter
 * \ingroup IntensityImageFilters  Multithreaded
 */

template<class TInputImage, class TOutputImage>
class ITK_EXPORT IntermodesThresholdImageFilter : 
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard Self typedef */
  typedef IntermodesThresholdImageFilter                      Self;
  typedef ImageToImageFilter<TInputImage,TOutputImage>  Superclass;
  typedef SmartPointer<Self>                            Pointer;
  typedef SmartPointer<const Self>                      ConstPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);  

  /** Runtime information support. */
  itkTypeMacro(IntermodesThresholdImageFilter, ImageToImageFilter);
  
  /** Image pixel value typedef. */
  typedef typename TInputImage::PixelType   InputPixelType;
  typedef typename TOutputImage::PixelType  OutputPixelType;
  
  /** Image related typedefs. */
  typedef typename TInputImage::Pointer  InputImagePointer;
  typedef typename TOutputImage::Pointer OutputImagePointer;

  typedef typename TInputImage::SizeType    InputSizeType;
  typedef typename TInputImage::IndexType   InputIndexType;
  typedef typename TInputImage::RegionType  InputImageRegionType;
  typedef typename TOutputImage::SizeType   OutputSizeType;
  typedef typename TOutputImage::IndexType  OutputIndexType;
  typedef typename TOutputImage::RegionType OutputImageRegionType;


  /** Image related typedefs. */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension );
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension );

  /** Set the "outside" pixel value. The default value 
   * NumericTraits<OutputPixelType>::Zero. */
  itkSetMacro(OutsideValue,OutputPixelType);
  
  /** Get the "outside" pixel value. */
  itkGetConstMacro(OutsideValue,OutputPixelType);

  /** Set the "inside" pixel value. The default value 
   * NumericTraits<OutputPixelType>::max() */
  itkSetMacro(InsideValue,OutputPixelType);
  
  /** Get the "inside" pixel value. */
  itkGetConstMacro(InsideValue,OutputPixelType);

  /** Set/Get the number of histogram bins. Defaults is 128. */
  itkSetClampMacro( NumberOfHistogramBins, unsigned long, 1, 
                    NumericTraits<unsigned long>::max() );
  itkGetConstMacro( NumberOfHistogramBins, unsigned long );

  /** max number of histogram smoothing iterations */
  itkSetMacro( MaxSmoothingIterations, unsigned long);
  itkGetConstMacro( MaxSmoothingIterations, unsigned long );

  /** select whether midpoint (intermode=true) or minimum between
  peaks is used */
  itkSetMacro( UseInterMode, bool);
  itkGetConstMacro( UseInterMode, bool );

  /** Get the computed threshold. */
  itkGetConstMacro(Threshold,InputPixelType);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(OutputEqualityComparableCheck,
    (Concept::EqualityComparable<OutputPixelType>));
  itkConceptMacro(InputOStreamWritableCheck,
    (Concept::OStreamWritable<InputPixelType>));
  itkConceptMacro(OutputOStreamWritableCheck,
    (Concept::OStreamWritable<OutputPixelType>));
  /** End concept checking */
#endif
protected:
  IntermodesThresholdImageFilter();
  ~IntermodesThresholdImageFilter(){};
  void PrintSelf(std::ostream& os, Indent indent) const;

  void GenerateInputRequestedRegion();
  void GenerateData ();

private:
  IntermodesThresholdImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  InputPixelType      m_Threshold;
  OutputPixelType     m_InsideValue;
  OutputPixelType     m_OutsideValue;
  unsigned long       m_NumberOfHistogramBins;
  unsigned            m_MaxSmoothingIterations;
  bool                m_UseInterMode;


}; // end of class

} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIntermodesThresholdImageFilter.txx"
#endif

#endif
