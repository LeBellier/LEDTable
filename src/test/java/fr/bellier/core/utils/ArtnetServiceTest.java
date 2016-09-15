package fr.bellier.core.utils;

import fr.bellier.core.entities.Box;
import java.awt.Color;
import java.util.LinkedList;
import java.util.List;
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
public class ArtnetServiceTest {

    private static ArtnetService service;

    public ArtnetServiceTest() {
    }

    @BeforeClass
    public static void setUpClass() {
        service = ArtnetService.getInstance();
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
    public void testConvertBoxToByte() {
        List<Box> box = new LinkedList<Box>();
        box.add(new Box(0, Color.red));
        box.add(new Box(1, new Color(120, 101, 255)));

        int[] actuals = service.colorToByteArray(box);
        int[] expecteds = {255, 0, 0, 120, 101, 255};

        Assert.assertArrayEquals(expecteds, actuals);

    }
}
