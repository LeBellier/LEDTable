package fr.bellier.testApplet.utils;

import org.junit.Assert;
import org.junit.Test;

/**
 * @author Bruno Bellier
 */
public class CoordinateConverterTest {

    //int [i][j] = int [7][11] = {int[11],int[11],int[11],int[11],int[11],int[11],int[11]}
    @Test
    public void testConvertTo1D() throws Exception {
        int iSize = 7, iCurrent = 1, jSize = 11, jCurrent = 5;
        Assert.assertEquals(16, CoordinateConverter.convertTo1D(iSize, jSize, iCurrent, jCurrent));
    }

    @Test
    public void testConvertTo2Di() throws Exception {
        int iSize = 7, jSize = 11, xCurrent = 16;
        Assert.assertEquals(1, CoordinateConverter.convertTo2Di(iSize, jSize, xCurrent));
    }

    @Test
    public void testConvertTo2Dj() throws Exception {
        int iSize = 7, jSize = 11, xCurrent = 16;
        Assert.assertEquals(5, CoordinateConverter.convertTo2Dj(iSize, jSize, xCurrent));
    }
}
