package fr.bellier.core;

import fr.azelart.artnetstack.domain.controller.Controller;
import fr.azelart.artnetstack.domain.controller.ControllerGoodInput;
import fr.azelart.artnetstack.domain.controller.ControllerGoodOutput;
import fr.azelart.artnetstack.domain.controller.ControllerPortType;
import fr.azelart.artnetstack.domain.enums.PortInputOutputEnum;
import fr.azelart.artnetstack.domain.enums.PortTypeEnum;
import fr.azelart.artnetstack.listeners.ServerListener;
import fr.azelart.artnetstack.server.ArtNetServer;
import fr.azelart.artnetstack.utils.ArtNetPacketEncoder;
import fr.bellier.core.entities.Box;
import fr.bellier.core.utils.ArtnetService;
import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Observer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author LeBellier
 */
public class ArtNetManager implements Observer {

    private Controller thisControler;
    private ArtNetServer artNetServer;
    private static long lastUpdate;

    public ArtNetManager() {
        createControler();

        try {
            artNetServer = new ArtNetServer();

            // Server listener
            artNetServer.addListenerServer(new ServerListener() {
                @Override
                public void onConnect() {
                    System.out.println("Connected");
                }

                @Override
                public void onTerminate() {
                    System.out.println("Disconnected");
                }
            });

            artNetServer.start();

        } catch (SocketException e) {
        } catch (UnknownHostException e) {
        }
    }

    private void createControler() {
        thisControler = new Controller();

        // Create one port
        final Map<Integer, ControllerPortType> vPorts = new HashMap<Integer, ControllerPortType>();
        ControllerPortType vPort1 = new ControllerPortType();
        vPort1.setInputArtNet(true);
        vPort1.setOutputArtNet(true);
        vPort1.setPort(0);
        vPort1.setType(PortTypeEnum.DMX512);
        vPort1.setDirection(PortInputOutputEnum.BOTH);
        vPorts.put(0, vPort1);

        // Set status port1 input
        final Map<Integer, ControllerGoodInput> vGoodInputsMap = new HashMap<Integer, ControllerGoodInput>();
        ControllerGoodInput vGoodInput1 = new ControllerGoodInput();
        vGoodInput1.setDisabled(false);
        vGoodInput1.setDataReceived(true);
        vGoodInput1.setIncludeDMXSIPsPackets(true);
        vGoodInput1.setIncludeDMXTestPackets(true);
        vGoodInput1.setIncludeDMXTextPackets(true);
        vGoodInput1.setReceivedDataError(false);
        vGoodInputsMap.put(0, vGoodInput1);

        // Set status port1 output
        final Map<Integer, ControllerGoodOutput> vGoodOutputsMap = new HashMap<Integer, ControllerGoodOutput>();
        ControllerGoodOutput vGoodOutput1 = new ControllerGoodOutput();
        vGoodOutput1.setDataTransmited(true);
        vGoodOutput1.setOutputPowerOn(true);
        vGoodOutput1.setOutputMergeArtNet(false);
        vGoodOutput1.setMergeLTP(false);
        vGoodOutput1.setIncludeDMXTextPackets(false);
        vGoodOutput1.setIncludeDMXTestPackets(false);
        vGoodOutput1.setIncludeDMXSIPsPackets(false);
        vGoodOutputsMap.put(0, vGoodOutput1);

        // Display
        thisControler.setScreen(false);

        thisControler.setGoodOutputMapping(vGoodOutputsMap);
        thisControler.setGoodInputMapping(vGoodInputsMap);
        thisControler.setPortTypeMap(vPorts);

        // Network
        thisControler.setNetwork("00");
        thisControler.setSubNetwork("00");
    }

    private void sendPacket(final String univers, final int dmx[]) {
        try {
            artNetServer.sendPacket(ArtNetPacketEncoder.encodeArtDmxPacket(univers, "0", dmx));
            System.out.println("SendPacket");
        } catch (IOException ex) {
            Logger.getLogger(ArtNetManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void update(Observable o, Object o1) {

        long now = System.currentTimeMillis();
        //System.out.print(now);
        //if (lastUpdate + 400 < now) {
        ArtnetService service = ArtnetService.getInstance();
        sendPacket("0", service.colorToByteArray((List<Box>) o1));
        //lastUpdate = now;
        //}
        //System.out.println();
    }
}
