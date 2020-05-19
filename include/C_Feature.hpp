#ifndef _C_Feature_H
#define _C_Feature_H
/*----------------------------------------------------------------------------
*
*	Module: CFeature
*	Author:	Jose Antonio Piedra Fernández
*	Date  :
*
*---------------------------- DESCRIPTION -----------------------------------
*---------------------------- CONSTRAINTS -----------------------------------
*
*	Computer:
*	O. S.   :
*	Compiler:
*	Others  :
*
*--------------------------------------------------------------------------*/

/*------------------------- IMPORTED MODULES ------------------------------*/
#include <stdio.h>
#include <map.h>
#include <list.h>
#include <C_Matrix.hpp>
#include <C_Image.hpp>
/*---------------------------- CONSTANTS ----------------------------------*/
#define NULO -1
#define NEUTRO 0
#define MaxCadena 30
#define MaxMatrixMoment 4  //Number The Moment Matrix (Index -> Moment,MomentT,MomentTR,MomentTRE)
#define MaxNeighbour 8
#define tam_buf 100

/*----------------------------- CLASSES -----------------------------------*/
class C_Feature
{
  public: // Types

    //To the Colum of Feature Matrix
    typedef enum {NumReg=1, FirstPointC, FirstPointR, Perimeter, Area, Volume,
        Volume2, Density, MinGrey, MaxGrey, MeanGrey, Stddev,
        BoundingBoxDy, BoundingBoxDx, BoundingBoxOy, BoundingBoxOx, BoundingBoxArea,
        GreyBaryCentery,GreyBaryCenterx, EquivDiameter, Extent,
        MajorAxis, MinorAxis, Orientation,ExcentricityMomentT,Irradiance,CentroideY,CentroideX,
        TopLefty, TopLeftx, TopRighty, TopRightx, RightTopy, RightTopx, RightBottomy, RightBottomx,
        BottomRighty, BottomRightx, BottomLefty, BottomLeftx, LeftBottomy, LeftBottomx, LeftTopy, LeftTopx,
        M1y, M1x, M2y, M2x, M2xy, ExcentricityInertia,
        invHu1,invHu2,invHu3,invHu4,invHu5,invHu6,invHu7,
        L1,L2,L3,L4,L5,L6,
        S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, P1, P2,
        MaxFeature=P2} FeatureT;

    //To the Feature Array
    typedef enum {ANumReg=0, AFirstPoint,AArea, AVolume, APerimeter, ADensity,
        AMinGrey, AMaxGrey, AMeanGrey,
        ABoundingBoxDx, ABoundingBoxDy, ABoundingBoxO, ABoundingBoxArea,
        AGreyBaryCenter, AStddev, AVolume2, AEquivDiameter, AExtent,
        AMajorAxis, AMinorAxis, AOrientation,AExcentricityMomentT,AIrradiance,ACentroide,
        ATopLeft, ATopRight, ARightTop, ARightBottom, ABottomRight, ABottomLeft, ALeftBottom, ALeftTop,
        ArangeMI,AM1x, AM1y, AM2x, AM2y, AM2xy, AExcentricityInertia,
        ArangeHu,AinvHu1,AinvHu2,AinvHu3,AinvHu4,AinvHu5,AinvHu6,AinvHu7,
        ArangeL,AL1,AL2,AL3,AL4,AL5,AL6,
        ArangeS,AS1, AS2, AS3, AS4, AS5, AS6, AS7, AS8, AS9, AS10, AS11, AP1, AP2,
        ArangeMT,AMoment,AMomentT,AMomentTR,AMomentTRE,
        AListNeigh,AListPerimeter,NumCharactConfig=AListPerimeter+1,
        FirstCharactConfig=ANumReg,LastCharactConfig=AListPerimeter} ArrayFeatureT;

    typedef char cad [MaxCadena];
    typedef cad CadenaT;

    //** List of  Perimeter **
    typedef list<C_Matrix::CoordT> ListPerimeter;
    typedef map<C_Matrix::ElementT, ListPerimeter, less <C_Matrix::ElementT>,allocator<C_Matrix::ElementT> > MapPerimeter;

    //** List of Neigbourhs **
    typedef C_Matrix::ElementT Neighbours [MaxNeighbour];
    typedef list<C_Matrix::ElementT> ListAdjacent; //The Adjacent Places
    typedef map<C_Matrix::ElementT, ListAdjacent, less <C_Matrix::ElementT>,allocator<C_Matrix::ElementT> > MapNeighb;//NumRegion <--> Map of Neighbours

private:

    //THE GLOBAL VARIABLES

    C_Matrix::IndexT ischaract [NumCharactConfig];

    CadenaT FeatureNames [MaxFeature+1];

    C_Matrix Charact;       //The image Feature (Var Static)
    C_Matrix CharactMoment; //The image Feature (Moments Dinamic)
    C_Matrix Moment;    //The Moments
    C_Matrix MomentT;   //The Centrals Normalities Moments to Traslation
    C_Matrix MomentTR;  //The Centrals Normalities Moments to Traslation and Rotation
    C_Matrix MomentTRE; //The Centrals Normalities Moments to Traslation, Rotation and Size

    MapNeighb MapNeighbour;
    MapPerimeter PlacesPerimeter;

    //The Header of Matrix ()
    char ** HeaderMat;
    int numcolHeader;

/*----------------------------- METHODS -----------------------------------*/

  public:
    // Constructor: empty Feature
    C_Feature ();

    // Constructor: creates an empty set of Feature
    C_Feature (C_Matrix::IndexT numrow,C_Matrix::IndexT incharact[NumCharactConfig]);

    // Destructor.
    ~C_Feature ();

// Copy of a Feature: overloading =
//    C_Feature& operator = (C_Feature& source);

    // Generate to empty constructor: creates an empty set of Feature
    void Generate(C_Matrix::IndexT numrow,C_Matrix::IndexT incharact[NumCharactConfig]);

    // Clear array of HeaderMat
    void ClearHeader();

    // Clear all the matrix , arrays and lists
    void Clear ();

//  private:
    //Assign value to Array Feature
    void AssignValue(C_Matrix::IndexT data, C_Matrix::IndexT value);

    //Control of Dependecy about differents Feature
    void ControlDependency();

    //Assign the name for each colum
    void AssignNameColum();

    //Assign the number of order for moment
    C_Matrix::IndexT AssignOrder();

    //Calculate the number of moments
    C_Matrix::IndexT CalculateNumMoment(C_Matrix::IndexT order);

    //Assign the index of CharactMoment to (Submatrix like Moment,etc.)
    void IndexCharactMoment(C_Matrix::IndexT order,C_Matrix::IndexT nummoment);

    //Search Row to Region
    C_Matrix::IndexT SearchRow(C_Matrix::ElementT numregion);

    //Search The Possible Neighbours
    void SearchNeighbours(C_Matrix &imageseg,C_Matrix::IndexT row,C_Matrix::IndexT col,Neighbours &Neighb);

    //Calculate Perimeter (4 or 8-Neighbours)
    void CalculatePerimeter(C_Matrix &imageseg,C_Matrix::IndexT row,C_Matrix::IndexT col,C_Matrix::IndexT rowregion,const int neighbour,ListPerimeter &Lista);

    //Insert Neighbours in the list.
    void InsertNeighbours(C_Matrix::ElementT numregion,C_Matrix::ElementT numadjacent);

    //Generate List of Neighbours (4 or 8-Neighbours)
    void GenerateNeighbours(C_Matrix &imageseg,C_Matrix::IndexT row,C_Matrix::IndexT col,const int numneighbour=4);

    // Calculate the datas of imagen
    // IF greylevel == true use the grey level of matrix original.
    void CalculateData(C_Matrix &imageorig,C_Matrix &imageseg,C_Matrix::IndexT row,C_Matrix::IndexT col,C_Matrix::IndexT rowregion,const bool greylevel,const int neighbour,ListPerimeter &Lista);

    // Calculate the moments of inertia M2x, M2y, M2xy and Excentricity
    // and Standars Desviation of the grey level intensities
    void InertiaStddev(C_Matrix &imageorig,C_Matrix &imageseg,C_Matrix::IndexT rowregion);

    // Calculate The Bounding Box (Point(X,Y), Width and Height
    void BoundigBox(C_Matrix &imageseg,C_Matrix::IndexT rowregion);

    // Calculate Extremal point
    void TopLeft(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void TopRight(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void RightTop(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void RightBottom(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void BottomRight(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void BottomLeft(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void LeftBottom(C_Matrix &imageseg,C_Matrix::IndexT rowregion);
    void LeftTop(C_Matrix &imageseg,C_Matrix::IndexT rowregion);

    // Calculate the extremal points in the region.
    void Extrema (C_Matrix &imageseg,C_Matrix::IndexT rowregion);

    //Calculate the density
    void CalculateDensity(C_Matrix::IndexT rowregion);

    //Calculate the Moments of inertia (M1) Total
    void CalculateM1Total(C_Matrix::IndexT rowregion);

    //Calculate the Mean of Grey
    void CalculateMeanGrey(C_Matrix::IndexT rowregion);

    //Calculate EquivDiameter
    //(Diameter of a circle with the same area as the region)
    void CalculateEquivDiameter(C_Matrix::IndexT rowregion);

    //Calculate Extent
    //(The porportion of the pixeles in the bounding box that are also in the region)
    void CalculateExtent(C_Matrix::IndexT rowregion);

    //Calculate GreyBaryCenter
    void CalculateGreyBaryCenter(C_Matrix::IndexT rowregion);

    //Calculate the Excentricity for the centrals normalities moments
    void CalculateExcentricityMomentT(C_Matrix::IndexT rowregion);

    //The Center of Ellipse
    void CalculateCentroideEllipse(C_Matrix::IndexT rowregion);

    //***** THE MOMENTS ******

    //Calculate the centrals moments
/*    C_Matrix::ElementT mc00(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc10();
    C_Matrix::ElementT mc01();
    C_Matrix::ElementT mc11(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc20(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc02(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc30(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc03(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc12(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mc21(C_Matrix::IndexT rowregion);

    //Calculate the centrals normalities moments
    //for p+q=2,3,...
    C_Matrix::ElementT mcn11(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mcn20(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mcn02(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mcn30(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mcn03(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mcn12(C_Matrix::IndexT rowregion);
    C_Matrix::ElementT mcn21(C_Matrix::IndexT rowregion);
  */
    //Calculate the centrals normalities moments
    //for p+q=2,3,...
    C_Matrix::ElementT mcn(C_Matrix::IndexT rowregion, C_Matrix::IndexT j, C_Matrix::IndexT k);

    //***** HU *****
    // Calculate the invariables seven moments
    //(Traslation,Rotation and Size)
    //about the moment of two and three order by HU.
    void InvHU(C_Matrix::IndexT rowregion);

    //***** S. MAITRA *****
    //Calculate the invariables six moments
    //(Traslation,Rotation,Size and Contraste) by S. Maitra
    void InvMaitraL(C_Matrix::IndexT rowregion);

    //***** THE TENSORIAL MOMENTS *****
    //Calculate the factorial
    C_Matrix::ElementT factorial(C_Matrix::IndexT n);

    //Calculate the centrals normalities moments
    //to Traslation (TENSORIAL MOMENTS)
    void mtjk(C_Matrix::IndexT rowregion,C_Matrix::IndexT j, C_Matrix::IndexT k);

    //Calculate the centrals normalities moments
    //to Traslation an Rotation (TENSORIAL MOMENTS)

    void AnguleOrientation(C_Matrix::IndexT rowregion);
    void MajorAxisEllipse(C_Matrix::IndexT rowregion);
    void MinorAxisEllipse(C_Matrix::IndexT rowregion);
    //Calculte the irradience of the image ellipse is F inside the ellipse and zero outside
    void CalculateIrradiance(C_Matrix::IndexT rowregion);

    void mrjk(C_Matrix::IndexT rowregion,C_Matrix::IndexT j, C_Matrix::IndexT k);


    //Calculate the centrals normalities moments
    //to Traslation, Rotation and Size (TENSORIAL MOMENTS)
    void mejk(const C_Matrix::IndexT rowregion, const C_Matrix::IndexT j, const C_Matrix::IndexT k);

    //Calculate the centrals normalities moments to Traslation (TENSORIAL MOMENTS)
    void TensorialMomentInvT(C_Matrix::IndexT rowregion);
    //Calculate the centrals normalities moments to Traslation
    //and Rotation (TENSORIAL MOMENTS)
    void TensorialMomentInvTR(C_Matrix::IndexT rowregion);
    //Calculate the centrals normalities moments to Traslation,
    //Rotation and Size (TENSORIAL MOMENTS)
    void TensorialMomentInvTRE(C_Matrix::IndexT rowregion);

    //***** ZERNIKE *****
    // Calculate the moment invariants expressed in terms of usual moments
    //Second Order
    void ZernikeS1(C_Matrix::IndexT rowregion);
    void ZernikeS2(C_Matrix::IndexT rowregion);

    //Third Order
    void ZernikeS3(C_Matrix::IndexT rowregion);
    void ZernikeS4(C_Matrix::IndexT rowregion);
    void ZernikeS5(C_Matrix::IndexT rowregion);
    void ZernikeS6(C_Matrix::IndexT rowregion);

    //Fourth Order
    void ZernikeS7(C_Matrix::IndexT rowregion);
    void ZernikeS8(C_Matrix::IndexT rowregion);
    void ZernikeS9(C_Matrix::IndexT rowregion);
    void ZernikeS10(C_Matrix::IndexT rowregion);
    void ZernikeS11(C_Matrix::IndexT rowregion);

    //Pseudo-invariants
    void ZernikeP1(C_Matrix::IndexT rowregion);
    void ZernikeP2(C_Matrix::IndexT rowregion);

    //Calculate All moments invariants and pseudo-invariants
    void ZernikeAllMoment(C_Matrix::IndexT rowregion);


    //***** ABSOLUTE VALUE *****
    void AbsoluteMI(C_Matrix::IndexT rowregion);
    void AbsoluteHu(C_Matrix::IndexT rowregion);
    void AbsoluteL(C_Matrix::IndexT rowregion);
    void AbsoluteS(C_Matrix::IndexT rowregion);
    void AbsoluteMT(C_Matrix::IndexT rowregion);

    //***** DINAMIC RANGE REDUCTION *****
    void ReductionMI(C_Matrix::IndexT rowregion);
    void ReductionHu(C_Matrix::IndexT rowregion);
    void ReductionL(C_Matrix::IndexT rowregion);
    void ReductionS(C_Matrix::IndexT rowregion);
    void ReductionMT(C_Matrix::IndexT rowregion);

    //***** GLOBAL CALCULATE *****

    // Extract the Feature of a number of place
    // IF greylevel == true use the grey level of matrix original.
    void AnalyzeFeature(C_Matrix &imageorig,C_Matrix &imageseg,C_Matrix::ElementT numregion,const bool greylevel=true,const int neighbour=8);

    // For all the places.
    void AnalyzeFeatureAllPlace(C_Matrix &imageorig,C_Matrix &imageseg,list<C_Matrix::ElementT> &Lista, const bool greylevel=true,const int neighbour=8);
    // For one place.
    void AnalyzeFeatureOnePlace(C_Matrix &imageorig,C_Matrix &imageseg,C_Matrix::ElementT numregion,const bool greylevel=true,const int neighbour=8);


    //***** PRINT OF Feature *****

    // Prints the set of Feature in the stadard output.
    void PrintCharact (C_Matrix::IndexT col);
    // For all the places.
    void PrintAllCharact (C_Matrix::IndexT incharact []);

    // Search The Moment of Colum (CharactMoment)
    void SearchMoment(C_Matrix &M,C_Matrix::IndexT data,int &p,int &q);
    // Prints the string of moments in the stadard output.
    void PrintStringMoment(C_Matrix::IndexT col);
    // Prints the set of moments in the stadard output.
    void PrintMoment (C_Matrix::IndexT col);
    // For all the places.
    void PrintAllMoment ();

    //Print List of Neighbours in the stadard output.
    void PrintNeighbours(C_Matrix::ElementT numregion,int colWidth,int maxDigits);
    // For all the places.
    void PrintAllNeighbours(int colWidth,int maxDigits);

    //Print List of Perimeter in the stadard output.
    void PrintPerimeter(C_Matrix::ElementT numregion,int colWidth,int maxDigits);
    // For all the places.
    void PrintAllPerimeter(int colWidth,int maxDigits);

    //Select the colum of matrix Feature to show
    int ColumShow(C_Matrix &mataux,C_Matrix::IndexT incharact [NumCharactConfig]);
    //Select the colum of matrix moment to show
    int ColumMoment(C_Matrix &mataux,C_Matrix::IndexT incharact [NumCharactConfig]);
    //Print all the Feature
    void PrintFeature(C_Matrix::IndexT incharact [NumCharactConfig]);


    //***** WRITE OF Feature *****

    void WriteStringMoment(FILE *out,C_Matrix::IndexT col);
    void WriteNeighbours(FILE *out,C_Matrix::ElementT numregion,int colWidth,int maxDigits);
    void WriteAllNeighbours(FILE *out,int colWidth,int maxDigits);
    void WritePerimeter(FILE *out,C_Matrix::ElementT numregion,int colWidth,int maxDigits);
    void WriteAllPerimeter(FILE *out,int colWidth,int maxDigits);

    void WriteFeature(const char * fileName,char *modo,C_Matrix::IndexT incharact [NumCharactConfig],bool todasregiones);
    void WriteMoment(const char * fileName,char *modo,C_Matrix::IndexT incharact [NumCharactConfig],bool todasregiones);
    void WriteListAdjacent(const char * fileName,char *modo,C_Matrix::IndexT incharact [NumCharactConfig],bool todasregiones);
    void WriteListPerimeter(const char * fileName,char *modo,C_Matrix::IndexT incharact [NumCharactConfig],bool todasregiones);

    void StringMoment(char *cad,C_Matrix::IndexT col);

/*----------------------------- EXTERN METHODS -----------------------------------*/

//public:
    //Read Number of places to segmentation image
    C_Matrix::ElementT static ReadNumberPlaces(C_Matrix &imageseg, list <C_Matrix::ElementT> & Lista);

    //Calculate Feature (In -> filename of images)
    void CalculateFeature(const char * FileOrig,const char * FileSeg,C_Matrix::IndexT whatcharact [NumCharactConfig],const bool &greylevel,const bool &allRegiones,const int &neighbour);
    //Calculate Feature (In -> matrix of images)
    void CalculateFeature(C_Matrix &imageorig,C_Matrix &imageseg,C_Matrix::IndexT whatcharact [NumCharactConfig],const bool &greylevel,const bool &allRegiones,const int &neighbour);
    //Calculate Feature (In -> matrix of images && list of regiones)
    void CalculateFeature(C_Matrix &imageorig,C_Matrix &imageseg,list<C_Matrix::ElementT> ListPlace, C_Matrix::IndexT whatcharact [NumCharactConfig],const bool &greylevel,const bool &allRegiones,const int &neighbour);


    //Save Feature
    void SaveFeature(const bool allRegiones,C_Matrix::IndexT whatcharact [NumCharactConfig]);

    //Extract Feature To New Format (Matrix Out, Header Matrix Out)
    //Only (Matrix Charact(With constant) && Matrix CharactMoment(With moments))
    void ExtractFeature(C_Matrix &CharactOut, char **& HeaderOut, const bool allRegiones, C_Matrix::IndexT whatcharact [NumCharactConfig]);
    //Write Feature To New Format (Matrix Out, Header Matrix Out) in out File
    //Only (Matrix Charact(With constant) && Matrix CharactMoment(With moments))
    void WriteExtractFeature(const char * fileName,C_Matrix &CharactOut);

    //****** Feature ******
    //Access to All Feature by row and col
    C_Matrix::ElementT c(const C_Matrix::IndexT row, const C_Matrix::IndexT col);
    //Access to All Feature by place number and col
    C_Matrix::ElementT car(const C_Matrix::ElementT numregion, const C_Matrix::IndexT col);

    C_Matrix::ElementT carFirstRow(void)    {return Charact.FirstRow();}
    C_Matrix::ElementT carLastRow(void)     {return Charact.LastRow();}
    C_Matrix::ElementT carFirstCol(void)    {return Charact.FirstCol();}
    C_Matrix::ElementT carLastCol(void)     {return Charact.LastCol();}
    C_Matrix::ElementT carRowN(void)        {return Charact.RowN();}
    C_Matrix::ElementT carColN(void)        {return Charact.ColN();}

    //****** Moment ******
    //Access to All Moment by row and col
    C_Matrix::ElementT m(const C_Matrix::IndexT row, const C_Matrix::IndexT col);
    //Access to All Moment by place number and col
    C_Matrix::ElementT mnt(const C_Matrix::ElementT row, const C_Matrix::IndexT col);

    //Access to Ordinary Moment by row and col
    C_Matrix::ElementT mN(const C_Matrix::IndexT row, const C_Matrix::IndexT p,const C_Matrix::IndexT q);
    //Access to Ordinary Moment by place number and col
    C_Matrix::ElementT mntN(const C_Matrix::ElementT numregion, const C_Matrix::IndexT p,const C_Matrix::IndexT q);

    //Access to Traslation Invariant Moment by row and col
    C_Matrix::ElementT mT(const C_Matrix::IndexT row, const C_Matrix::IndexT p,const C_Matrix::IndexT q);
    //Access to Traslation Invariant Moment by place number and col
    C_Matrix::ElementT mntT(const C_Matrix::ElementT numregion, const C_Matrix::IndexT p,const C_Matrix::IndexT q);

    //Access to Rotation Invariant Moment by place number and col
    C_Matrix::ElementT mR(const C_Matrix::IndexT row, const C_Matrix::IndexT p,const C_Matrix::IndexT q);
    //Access to Rotation Invariant Moment by place number and col
    C_Matrix::ElementT mntR(const C_Matrix::ElementT numregion, const C_Matrix::IndexT p,const C_Matrix::IndexT q);

    //Access to Size Invariant Moment by place number and col
    C_Matrix::ElementT mE(const C_Matrix::IndexT row, const C_Matrix::IndexT p,const C_Matrix::IndexT q);
    //Access to Size Invariant Moment by place number and col
    C_Matrix::ElementT mntE(const C_Matrix::ElementT numregion, const C_Matrix::IndexT p,const C_Matrix::IndexT q);

    C_Matrix::ElementT mntFirstRow(void)    {return CharactMoment.FirstRow();}
    C_Matrix::ElementT mntLastRow(void)     {return CharactMoment.LastRow();}
    C_Matrix::ElementT mntFirstCol(void)    {return CharactMoment.FirstCol();}
    C_Matrix::ElementT mntLastCol(void)     {return CharactMoment.LastCol();}
    C_Matrix::ElementT mntRowN(void)        {return CharactMoment.RowN();}
    C_Matrix::ElementT mntColN(void)        {return CharactMoment.ColN();}

    //Access to all ListAdjacent
    C_Feature::MapNeighb MapAdjacent(void)    {return MapNeighbour;}
    //Access to ListAdjacent by place number
    C_Feature::ListAdjacent ListAdjacentPlace(C_Matrix::ElementT numregion);

    //Access to all ListPerimeter
    C_Feature::MapPerimeter MapPlacesPerimeter(void)    {return PlacesPerimeter;}
    //Access to ListPerimeter by place number
    C_Feature::ListPerimeter C_Feature::ListPerimeterPlace(C_Matrix::ElementT numregion);

    //Access to The Intern Configuration Charact Array
    void CadConfig(C_Matrix::IndexT config [NumCharactConfig]){ config = ischaract;}
    //Access to One Intern Configuration Charact by col number
    C_Matrix::IndexT Config(C_Matrix::IndexT col);

    //Access to The Name of Charact Array
    void CadNameCharact(CadenaT cadname[MaxFeature+1]){ cadname = FeatureNames;}
    //Access to One Name of Charact by col number
    void NameCharact(char *cad,C_Matrix::IndexT col);

    //Access to One Name Normal Moment of CharactMoment by moment Number
    void StringMomentN(char *cad,C_Matrix::IndexT p,C_Matrix::IndexT q){StringMoment(cad,Moment(p,q));}
    //Access to One Name Invariant Traslation Moment of CharactMoment by moment Number
    void StringMomentT(char *cad,C_Matrix::IndexT p,C_Matrix::IndexT q){StringMoment(cad,MomentT(p,q));}
    //Access to One Name Invariant Rotation Moment of CharactMoment by moment Number
    void StringMomentR(char *cad,C_Matrix::IndexT p,C_Matrix::IndexT q){StringMoment(cad,MomentTR(p,q));}
    //Access to One Name Invariant Size Moment of CharactMoment by moment Number
    void StringMomentE(char *cad,C_Matrix::IndexT p,C_Matrix::IndexT q){StringMoment(cad,MomentTRE(p,q));}


    //**** READ AND WRITE ABOUT THE CONFIGURATION OF Feature ****
    C_Matrix::IndexT static SearchConfiguration (char *car);
    //Read the Configuration array of Feature (of a file)
    int static ReadConfiguration(const char *filename, char *modo, C_Matrix::IndexT whatcharact [NumCharactConfig]);
    //Write the Configuration array of Feature (of a file)
    int static WriteConfiguration(const char *filename, char *modo, C_Matrix::IndexT whatcharact [NumCharactConfig]);

/*----------------------------- END EXTERN METHODS -----------------------------------*/
};
#endif
