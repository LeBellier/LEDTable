package fr.bellier.core.utils;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 *
 * @author LeBellier
 */
public class CoordinateConverterTest {

    private static CoordinateConverter coordinateConverter;

    public CoordinateConverterTest() {
    }

    @BeforeClass
    public static void setUpClass() {
        coordinateConverter = CoordinateConverter.getInstance();
    }

    @AfterClass
    public static void tearDownClass() {
    }

    @Before
    public void setUp() {
    }

    @After
    public void tearDown() {
    }

    @Test
    public void testConvertRCToRuban() throws Exception {
        int iSize = 11, iCurrent = 0, jSize = 7, jCurrent = 3;
        Assert.assertEquals(3, coordinateConverter.convertRCToRuban(iSize, jSize, iCurrent, jCurrent));

        iSize = 11;
        iCurrent = 1;
        jSize = 7;
        jCurrent = 2;
        Assert.assertEquals(11, coordinateConverter.convertRCToRuban(iSize, jSize, iCurrent, jCurrent));

        iSize = 11;
        iCurrent = 2;
        jSize = 7;
        jCurrent = 4;
        Assert.assertEquals(18, coordinateConverter.convertRCToRuban(iSize, jSize, iCurrent, jCurrent));

        iSize = 11;
        iCurrent = 3;
        jSize = 7;
        jCurrent = 2;
        Assert.assertEquals(25, coordinateConverter.convertRCToRuban(iSize, jSize, iCurrent, jCurrent));
    }

    @Test
    public void testConvert1DTo1D() throws Exception {
        int iSize = 11, jSize = 7, xCurrent = 3;
        Assert.assertEquals(3, coordinateConverter.convert1DTo1D(iSize, jSize, xCurrent));

        iSize = 11;
        jSize = 7;
        xCurrent = 9;
        Assert.assertEquals(11, coordinateConverter.convert1DTo1D(iSize, jSize, xCurrent));

        iSize = 11;
        jSize = 7;
        xCurrent = 18;
        Assert.assertEquals(18, coordinateConverter.convert1DTo1D(iSize, jSize, xCurrent));

        iSize = 11;
        jSize = 7;
        xCurrent = 23;
        Assert.assertEquals(25, coordinateConverter.convert1DTo1D(iSize, jSize, xCurrent));
    }

    //int [i][j] = int [7][11] = {int[11],int[11],int[11],int[11],int[11],int[11],int[11]}
    @Test
    public void testConvertRCToIndex() throws Exception {
        int iSize = 7, iCurrent = 1, jSize = 11, jCurrent = 5;
        Assert.assertEquals(16, coordinateConverter.convertRCToIndex(iSize, jSize, iCurrent, jCurrent));
    }

    @Test
    public void testConvertIndexToRC() throws Exception {
        int iSize = 7, jSize = 11, xCurrent = 16;
        Assert.assertEquals(1, coordinateConverter.convertIndexToRC(iSize, jSize, xCurrent)[0]);
        Assert.assertEquals(5, coordinateConverter.convertIndexToRC(iSize, jSize, xCurrent)[1]);
    }
}
