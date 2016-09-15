package fr.bellier.testApplet.utils;

import fr.bellier.testApplet.entities.Box;
import java.awt.Color;
import java.util.LinkedList;
import java.util.List;
import org.junit.Assert;
import org.junit.Test;

/**
 * @author Bruno Bellier
 */
public class ArtNetServiceTest {

    @Test
    public void testConvertBoxToByte() {
        List<Box> box = new LinkedList<Box>();
        box.add(new Box(0, Color.red));
        box.add(new Box(1, new Color(120, 101, 255)));

        ArtNetService service = new ArtNetService();
        int[] actuals = service.colorToByteArray(box);
        int[] expecteds = {255, 0, 0, 120, 101, 255};

        Assert.assertArrayEquals(expecteds, actuals);

    }
}
