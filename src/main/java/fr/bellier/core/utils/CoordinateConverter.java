package fr.bellier.core.utils;

/**
 *
 * @author LeBellier
 */
public class CoordinateConverter {

    private CoordinateConverter() {
    }

    public static CoordinateConverter getInstance() {
        return INSTANCE;
    }

    private static final CoordinateConverter INSTANCE = new CoordinateConverter();

    /*
    Définition des systemes de coordonnées :
        RC: R appartient[0..iSize-1]
            C appartient[0..jSize-1]

        Index: x appartient [0..xSize] avec cette forme
     *   0  1  2  3  4  5  6
     *   7  8  9 10 11 12 13
     *  14 15 16 17 18 19 20
     *  21 22 23 24 25 26 27

        Ruban: x appartient [0..xSize] avec cette forme
     *   0  1  2  3  4  5  6
     *  13 12 11 10  9  8  7
     *  14 15 16 17 18 19 20
     *  27 26 25 24 23 22 21
     */
    /**
     * convert From Index to Ruban or reverse
     *
     * @param iSize ex = 4
     * @param jSize ex = 7
     * @param xCurrent
     * @return The other xCurrent
     */
    public int convert1DTo1D(int iSize, int jSize, int xCurrent) {
        if (((xCurrent / jSize) % 2) == 0) {
            return xCurrent;
        } else {
            return (xCurrent / jSize + 1) * jSize - (xCurrent % jSize + 1);
        }
    }

    /**
     * convert From Index to RC
     *
     * @param iSize ex=5
     * @param jSize ex=7
     * @param xCurrent
     * @return [iCurrent,jCurrent]
     */
    public int[] convertIndexToRC(int iSize, int jSize, int xCurrent) {
        int[] result = {xCurrent / jSize, xCurrent % jSize};
        return result;
    }

    /**
     * convert From RC to Index
     *
     * @param iSize ex=5
     * @param jSize ex=7
     * @param iCurrent
     * @param jCurrent
     * @return xCurrent=iCurrent*jSize+jCurrent
     */
    public int convertRCToIndex(int iSize, int jSize, int iCurrent, int jCurrent) {
        return iCurrent * jSize + jCurrent;
    }

    /**
     * convert From RC to Ruban
     *
     * @param iSize ex = 4
     * @param jSize ex = 7
     * @param iCurrent
     * @param jCurrent
     * @return xCurrent
     */
    public int convertRCToRuban(int iSize, int jSize, int iCurrent, int jCurrent) {
        if ((iCurrent % 2) == 0) {
            return iCurrent * jSize + jCurrent;
        } else {
            return (iCurrent + 1) * jSize - (jCurrent + 1);
        }
    }

}
