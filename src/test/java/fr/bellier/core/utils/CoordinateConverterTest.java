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

    //int [i][j] = int [7][11] = {int[11],int[11],int[11],int[11],int[11],int[11],int[11]}
    @Test
    public void testConvertTo1D() throws Exception {
        int iSize = 7, iCurrent = 1, jSize = 11, jCurrent = 5;
        Assert.assertEquals(16, coordinateConverter.convertTo1D(iSize, jSize, iCurrent, jCurrent));
    }

    @Test
    public void testConvertTo2Di() throws Exception {
        int iSize = 7, jSize = 11, xCurrent = 16;
        Assert.assertEquals(1, coordinateConverter.convertTo2Di(iSize, jSize, xCurrent));
    }

    @Test
    public void testConvertTo2Dj() throws Exception {
        int iSize = 7, jSize = 11, xCurrent = 16;
        Assert.assertEquals(5, coordinateConverter.convertTo2Dj(iSize, jSize, xCurrent));
    }
}
