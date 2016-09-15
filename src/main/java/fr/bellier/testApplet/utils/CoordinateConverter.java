/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.bellier.testApplet.utils;

/**
 *
 * @author bruno
 */
public class CoordinateConverter {

    /**
     * convert From [0..4][0..6] to [0..34]
     *
     * @param iSize ex=5
     * @param jSize ex=7
     * @param iCurrent
     * @param jCurrent
     * @return xCurrent=iCurrent*jSize+jCurrent
     */
    static public int convertTo1D(int iSize, int jSize, int iCurrent, int jCurrent) {
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
    static public int convertTo2Di(int iSize, int jSize, int xCurrent) {
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
    static public int convertTo2Dj(int iSize, int jSize, int xCurrent) {
        return xCurrent % jSize;
    }
}
