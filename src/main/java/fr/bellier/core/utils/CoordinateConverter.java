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

    /**
     * convert From [0..4][0..6] to [0..34]
     *
     * @param iSize ex=5
     * @param jSize ex=7
     * @param iCurrent
     * @param jCurrent
     * @return xCurrent=iCurrent*jSize+jCurrent
     */
    public int convertTo1D(int iSize, int jSize, int iCurrent, int jCurrent) {
        return iCurrent * jSize + jCurrent;
    }

    /**
     * convert From [0..4][0..6] to [0..34]
     *
     * @param iSize ex=5
     * @param jSize ex=7
     * @param xCurrent
     * @return iCurrent=xCurrent%jSize
     */
    public int convertTo2Di(int iSize, int jSize, int xCurrent) {
        return xCurrent / jSize;
    }

    /**
     * convert From [0..4][0..6] to [0..34]
     *
     * @param iSize ex=5
     * @param jSize ex=7
     * @param xCurrent
     * @return jCurrent=xCurrent/jSize
     */
    public int convertTo2Dj(int iSize, int jSize, int xCurrent) {
        return xCurrent % jSize;
    }
}
